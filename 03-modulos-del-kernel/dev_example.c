#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Federico Rossi");
MODULE_DESCRIPTION("Dispositivo virtual /dev/hello");
MODULE_VERSION("1.0");

#define MSG "Hola desde /dev/hello!\n"

static ssize_t hello_read(struct file *file, char __user *buf,
                          size_t count, loff_t *ppos)
{
    return simple_read_from_buffer(buf, count, ppos, MSG, strlen(MSG));
}

static const struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .read  = hello_read,
};

static struct miscdevice hello_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "hello",
    .fops = &hello_fops,
    .mode = 0666
};

static int __init hello_init(void)
{
    int ret = misc_register(&hello_device);
    if (ret)
        printk(KERN_ERR "No se pudo registrar /dev/hello\n");
    else
        printk(KERN_INFO "/dev/hello registrado!\n");
    return ret;
}

static void __exit hello_exit(void)
{
    misc_deregister(&hello_device);
    printk(KERN_INFO "/dev/hello eliminado\n");
}

module_init(hello_init);
module_exit(hello_exit);