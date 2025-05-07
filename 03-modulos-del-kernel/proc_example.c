#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Federico Rossi");
MODULE_DESCRIPTION("/proc ejemplo de escritura");

#define PROC_NAME "mi_modulo_proc"

static int mostrar_info(struct seq_file *m, void *v)
{
    seq_printf(m, "Hola desde el kernel!\n");
    seq_printf(m, "Valor de jiffies: %lu\n", jiffies);
    return 0;
}

static int abrir_proc(struct inode *inode, struct file *file)
{
    return single_open(file, mostrar_info, NULL);
}

static const struct proc_ops proc_file_ops = {
    .proc_open    = abrir_proc,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

static int __init proc_mod_init(void)
{
    proc_create(PROC_NAME, 0, NULL, &proc_file_ops);
    printk(KERN_INFO "proc_example: módulo cargado, lee /proc/%s\n", PROC_NAME);
    return 0;
}

static void __exit proc_mod_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "proc_example: módulo descargado\n");
}

module_init(proc_mod_init);
module_exit(proc_mod_exit);