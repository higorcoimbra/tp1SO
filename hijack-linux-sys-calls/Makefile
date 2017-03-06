obj-m	:= hijack-syscall.o

KDIR    := /lib/modules/2.6.32.5/build

PWD    := `pwd`

default:
	make -C $(KDIR) M=$(PWD) modules

