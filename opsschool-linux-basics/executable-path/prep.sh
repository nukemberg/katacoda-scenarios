#!/bin/bash

mkdir /root/bin
apt update > /dev/null
apt install -y build-essential strace ltrace > /dev/null
gcc -o /root/bin/hello hello.c

echo 'Ready!'