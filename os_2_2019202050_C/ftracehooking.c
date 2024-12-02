#include "ftracehooking.h"
#define __NR_ftrace 336

typedef asmlinkage int (*sys_call_ptr_t)(const struct pt_regs *);
sys_call_ptr_t *syscall_table;

sys_call_ptr_t real_ftrace;

pid_t proc_pid;
int open_count;
int close_count;
int read_count;
int write_count;
int lseek_count;
char file_name[100];
size_t read_bytes;
size_t written_bytes;
ktime_t nanoseconds;

EXPORT_SYMBOL(open_count);
EXPORT_SYMBOL(close_count);
EXPORT_SYMBOL(read_count);
EXPORT_SYMBOL(write_count);
EXPORT_SYMBOL(lseek_count);
EXPORT_SYMBOL(file_name);
EXPORT_SYMBOL(read_bytes);
EXPORT_SYMBOL(written_bytes);

static asmlinkage int ftrace(const struct pt_regs *regs)
{
   if(regs->di != 0)
   {
      nanoseconds = ktime_get_ns();
      proc_pid = regs->di;
      open_count = 0;
      close_count = 0;
       read_count = 0;
      write_count = 0;
      lseek_count = 0;
      file_name[0] = '\0';
      read_bytes = 0;
      written_bytes = 0;
      printk("OS Assignment2 ftrace [%d] Start\n",proc_pid);      
   }
   else
   {
      printk("[2019202050] /%s file[%s] stats [x] read - %d / written - %d\n",current -> comm,(char*)file_name,(int)read_bytes,(int)written_bytes);
      printk("[trace time: %lluns] open[%d] close[%d] read[%d] write[%d] lseek[%d]\n",(ktime_get_ns()-nanoseconds),open_count,close_count,read_count,write_count,lseek_count);
      printk("OS Assignment2 ftrace [%d] End\n",proc_pid);
   }
   return 0;

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
   syscall_table[__NR_ftrace] = ftrace;
   return 0;
}

static void __exit hooking_exit(void)
{
   make_rw(syscall_table);
   syscall_table[__NR_ftrace] = real_ftrace;
   make_ro(syscall_table);
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
