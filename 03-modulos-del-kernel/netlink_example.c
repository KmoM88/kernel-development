#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/sock.h>

#define NETLINK_USER 31

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Federico Rossi");
MODULE_DESCRIPTION("Comunicacion entre kernel y espacio de usuario usando netlink");
MODULE_VERSION("1.0");

struct sock *nl_sk = NULL;

static void hello_nl_recv(struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
    char *msg = "Hola desde el kernel (netlink)!";
    struct sk_buff *skb_out;
    int pid, msg_size = strlen(msg), res;

    nlh = (struct nlmsghdr *)skb->data;
    pid = nlh->nlmsg_pid; // PID del proceso usuario

    skb_out = nlmsg_new(msg_size, GFP_KERNEL);
    if (!skb_out) {
        printk(KERN_ERR "No se pudo alocar skb\n");
        return;
    }

    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
    strncpy(nlmsg_data(nlh), msg, msg_size);

    res = netlink_unicast(nl_sk, skb_out, pid, 0);
    if (res < 0)
        printk(KERN_INFO "Fallo al enviar mensaje\n");
}

static int __init hello_init(void)
{
    struct netlink_kernel_cfg cfg = {
        .input = hello_nl_recv,
    };

    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
    if (!nl_sk) {
        printk(KERN_ALERT "Error creando socket netlink.\n");
        return -10;
    }

    printk(KERN_INFO "Modulo netlink_hello cargado.\n");
    return 0;
}

static void __exit hello_exit(void)
{
    netlink_kernel_release(nl_sk);
    printk(KERN_INFO "Modulo netlink_hello descargado.\n");
}

module_init(hello_init);
module_exit(hello_exit);
