#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/errno.h> 
#include <linux/types.h>
#include <linux/unistd.h>
#include <asm/cacheflush.h>  
#include <asm/page.h>  
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/kallsyms.h>
#include <asm/string.h>
#include <linux/cred.h>

unsigned long *syscall_table;
asmlinkage int (*original_remove)(int dirfd, const char *pathname, int flags);
asmlinkage int (*new_getuid)();

module_param(syscall_table, ulong, S_IRUGO);

int set_addr_rw(long unsigned int _addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

    if (pte->pte &~ _PAGE_RW) pte->pte |= _PAGE_RW;
}

int set_addr_ro(long unsigned int _addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(_addr, &level);

    pte->pte = pte->pte &~_PAGE_RW;
}

asmlinkage int new_remove(int dirfd,const char *pathname, int flags) {

    printk(KERN_ALERT "PID %i File:%s\n", current->pid, pathname);
    return (*original_remove)(dirfd, pathname, flags);
}

static int init(void) {

    printk(KERN_ALERT "\nHIJACK INIT\n");

    set_addr_rw((unsigned long)syscall_table);

    original_remove = (void *)syscall_table[__NR_unlinkat];

    syscall_table[__NR_unlinkat] = new_remove;  

    //GPF_ENABLE;

    return 0;
}

static void exit(void) {

    syscall_table[__NR_unlinkat] = original_remove;  
    set_addr_ro((unsigned long)syscall_table);

    //GPF_DISABLE;    

    printk(KERN_ALERT "MODULE EXIT\n");

    return;
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Higor Coimbra");
MODULE_DESCRIPTION("Hijack of remove function");
module_init(init);
module_exit(exit);

