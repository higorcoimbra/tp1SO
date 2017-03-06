#! /bin/bash

sudo rmmod hijack-syscall.ko
sudo ./load.sh
touch teste2
rm teste2
sudo cat /var/log/syslog | tail -2
