obj-m += hello.o

all:
	make -C /home/$(USER)/linux M=$(PWD) modules

clean:
	make -C /home/$(USER)/linux M=$(PWD) clean