#!/bin/bash

mkdir /root/bin
apt update
apt install -y build-essential strace ltrace
gcc -o /root/bin/hello hello.c