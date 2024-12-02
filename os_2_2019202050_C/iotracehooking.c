#include "ftracehooking.h"

#define __NR_read 0
#define __NR_write 1
#define __NR_open 2
#define __NR_close 3
#define __NR_lseek 8

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *);
sys_call_ptr_t *syscall_table;

sys_call_ptr_t real_open;
sys_call_ptr_t real_close;
sys_call_ptr_t real_read;
sys_call_ptr_t real_write;
sys_call_ptr_t real_lseek;

extern int open_count;
extern int close_count;
extern int read_count;
extern int write_count;
extern int lseek_count;
extern char file_name[100];
extern size_t read_bytes;
extern size_t written_bytes;

static asmlinkage long ftrace_open(const struct pt_regs *regs)
{
   strncpy_from_user(file_name,(char*)regs->di,sizeof(file_name));
   open_count++;
   return real_open(regs);
}

static asmlinkage long ftrace_close(const struct pt_regs *regs)
{
   close_count++;
   return real_close(regs);
}

static asmlinkage long ftrace_read(const struct pt_regs *regs)
{
   read_bytes += regs->dx;
   read_count++;
   return real_read(regs);
}

static asmlinkage long ftrace_write(const struct pt_regs *regs)
{
   written_bytes += regs->dx;
   write_count++;
   return real_write(regs);
}

static asmlinkage long ftrace_lseek(const struct pt_regs *regs)
{
   lseek_count++;
   return real_lseek(regs);
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
   real_open = syscall_table[__NR_open];
   syscall_table[__NR_open] = ftrace_open;

   real_close = syscall_table[__NR_close];
        syscall_table[__NR_close] = ftrace_close;

   real_read = syscall_table[__NR_read];
        syscall_table[__NR_read] = ftrace_read;

   real_write = syscall_table[__NR_write];
        syscall_table[__NR_write] = ftrace_write;

   real_lseek = syscall_table[__NR_lseek];
        syscall_table[__NR_lseek] = ftrace_lseek;
   return 0;
}

static void __exit hooking_exit(void)
{
   syscall_table[__NR_open] = real_open;
   syscall_table[__NR_close] = real_close;
   syscall_table[__NR_read] = real_read;
   syscall_table[__NR_write] = real_write;
   syscall_table[__NR_lseek] = real_lseek;
   make_ro(syscall_table);
}   

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
