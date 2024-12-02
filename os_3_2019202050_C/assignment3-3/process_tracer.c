#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <asm/syscall_wrapper.h>
#include <asm/uaccess.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/list.h>

#define __NR_ftrace 336
typedef asmlinkage int (*sys_call_ptr_t)(const struct pt_regs *);
sys_call_ptr_t *syscall_table;
sys_call_ptr_t real_ftrace;
struct task_struct *task;
struct task_struct *findtask;
struct list_head *findlist;
int listcount;

static asmlinkage pid_t process_tracer(const struct pt_regs *regs)
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
   task = pid_task(find_vpid(regs->di),PIDTYPE_PID);
   printk("##### TASK INFORMATION of \"[%lu] %s\" #####\n",regs->di,task->comm);

   /*Get state*/
   if(task->state == TASK_RUNNING){printk("- task state : Running or ready\n");}
   else if(task->state == TASK_INTERRUPTIBLE){printk("- task state : Wait\n");}
   else if(task->state == TASK_UNINTERRUPTIBLE){printk("- task state : Wait with ignoring all signals\n");}
   else if(task->state == __TASK_STOPPED){printk("- task state : Stopped\n");}
   else if(task->exit_state == EXIT_ZOMBIE){printk("- task state : Zombie process\n");}
   else if(task->exit_state == EXIT_DEAD){printk("- task state : Dead\n");}
   else{printk("- task state : etc.\n");}

   /*Group leader*/
   printk("- Process Group Leader : [%d] %s\n",task->group_leader->pid,task->group_leader->comm);

   /*Context Switch*/
   printk("- Number of context switches : %lu\n",task->nvcsw);

   /*fork count*/
   printk("- Number of calling fork() : %d\n",task->fork_count);

   /*parent*/
   printk("- it's parent process : [%d] %s\n",task->real_parent->pid,task->real_parent->comm);

   /*sibling*/
   listcount = 0;
   printk("- it's sibling process(es) : \n");
   list_for_each(findlist,&task->real_parent->children)
   {
      findtask = list_entry(findlist, struct task_struct,sibling);
      if(findtask->pid == task->pid){continue;}
      printk("\t\t> [%d] %s \n",findtask->pid,findtask->comm);
      listcount++;
   }
   printk("\t\t> This process has %d sibling process(es)\n",listcount);

   /*children*/
   listcount = 0;
   printk("- it's child process(es) : \n");
   list_for_each(findlist,&task->children)
   {
      findtask = list_entry(findlist, struct task_struct,sibling);
      printk("\t\t> [%d] %s \n",findtask->pid,findtask->comm);
      listcount++;
   }
   printk("\t\t> This process has %d child process(es)\n",listcount);

   /*END*/
   printk("##### END OF INFORMATION #####\n");
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
   syscall_table[__NR_ftrace] = process_tracer;
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