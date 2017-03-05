obj-m	:= hijack-syscall.o

KDIR    := /lib/modules/4.2.0-16-generic/build

PWD    := `pwd`

default:
	make -C $(KDIR) M=$(PWD) modules

