obj-m += hello.o
obj-m += proc_example.o
obj-m += dev_example.o
obj-m += netlink_example.o

all:
	make -C /home/$(USER)/linux M=$(PWD) modules

clean:
	make -C /home/$(USER)/linux M=$(PWD) clean