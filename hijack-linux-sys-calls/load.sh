#!/bin/bash

SYS_MAP=`ls /boot/System.map-2.6.32.5`

SYS_CALL_ADDR=0x`cat $SYS_MAP | grep sys_call_table | cut -f1 -d' '`

if [ 'X$SYS_CALL_ADDR' == 'X' ]
then
	echo "Can't find the system call table address."
	exit 1
fi

echo 'System call table address =' $SYS_CALL_ADDR

echo 'Building..'
make &> /dev/null

echo 'Loading..'
insmod hijack-syscall.ko syscall_table=$SYS_CALL_ADDR 

if [ $? -eq 0 ]
then
	echo "Module loaded."
fi
