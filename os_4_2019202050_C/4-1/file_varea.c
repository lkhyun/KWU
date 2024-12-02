#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <asm/syscall_wrapper.h>
#include <asm/uaccess.h>
#include <linux/pid.h>
#include <linux/sched/mm.h>
#include <linux/mm_types.h>

#define __NR_ftrace 336
typedef asmlinkage int (*sys_call_ptr_t)(const struct pt_regs *);
sys_call_ptr_t *syscall_table;
sys_call_ptr_t real_ftrace;
struct task_struct *task;
struct task_struct *findtask;
struct mm_struct *task_memory;
struct vm_area_struct *vm;
char filepath[512];

static asmlinkage pid_t file_varea(const struct pt_regs *regs)
{
   /*input validation test */
   if(regs->di < 1){return -1;}
   for_each_process(findtask)
   {
      if (findtask->pid == regs->di)
      {
         break;
      }
   }
   if(findtask->pid != regs->di)
   {
      return -1;
   }
   /*Get task_struct with pid*/
   task = pid_task(find_vpid(regs->di), PIDTYPE_PID);
   printk("######## Loaded files of a process '%s(%lu)' in VM ########\n", task->comm, regs->di);
   task_memory = get_task_mm(task);

   if (task_memory)// task_memory가 NULL이 아닌지 확인
   { 
      vm = task_memory->mmap;
      while (vm != NULL)
      {
         if (vm->vm_file)
         {
            printk("mem[%lx~%lx] code[%lx~%lx] data[%lx~%lx] heap[%lx~%lx] %s\n",
                   vm->vm_start, vm->vm_end,
                   task_memory->start_code, task_memory->end_code,
                   task_memory->start_data, task_memory->end_data,
                   task_memory->start_brk, task_memory->brk,
                   d_path(&(vm->vm_file->f_path), filepath, 512));
         }
         else
         {
            printk("mem[%lx~%lx] associated file is not exist\n", vm->vm_start, vm->vm_end);
         }
         vm = vm->vm_next;
      }
      mmput(task_memory);
   }
   else
   {
      printk("Error: task_memory is NULL\n");
   }

   /*END*/
   printk("############################################################\n");
   return regs->di;

}

void make_rw(void *addr)
{
   unsigned int level;
   pte_t *pte = lookup_address((u64)addr, &level);
   if(pte->pte &~ _PAGE_RW)
      pte->pte |= _PAGE_RW;
}

void make_ro(void *addr)
{
   unsigned int level;
   pte_t *pte = lookup_address((u64)addr, &level);

   pte->pte = pte->pte &~ _PAGE_RW;
}

static int __init hooking_init(void)
{
   syscall_table = (sys_call_ptr_t*) kallsyms_lookup_name("sys_call_table");

   make_rw(syscall_table);
   real_ftrace = syscall_table[__NR_ftrace];
   syscall_table[__NR_ftrace] = file_varea;
   return 0;
}

static void __exit hooking_exit(void)
{
   syscall_table[__NR_ftrace] = real_ftrace;
   make_ro(syscall_table);
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
