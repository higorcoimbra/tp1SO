#! /bin/bash

rmmod hijack-syscall.ko
./load.sh
touch teste2
rm teste2
cat /var/log/syslog | tail -2
