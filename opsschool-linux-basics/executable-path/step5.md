# Binaries and interpreters
Linux can execute several types of files, most are binary - such as the ELF64 which the standard format in Linux. The exact list of supported format depends on how the kernel was compiled and the loaded modules. The 

Linux can also use an _interpreter_ to execute files, in which case the interpreter is executed and given the file-to-be-executed as a parameter. This is what happens when the Kernel executes a script - a text file that starts with a sha-bang `#!`. The kernel can also be configured to support arbitrary misc formats using external interpreters, see  [binfmt_misc](https://www.kernel.org/doc/html/latest/admin-guide/binfmt-misc.html) for more details.

How does the Kernel know what format a file is? it looks at the first bytes of the file and tests for ["magic"](https://linux.die.net/man/5/magic) patterns. The `file` command uses the magic to identify file types - try it `file /root/bin/hello`{{execute}}

An binary file (e.g. ELF64) can be _dynamically_ or _statically_ linked. The difference is that statically linked files bundle all of their required libraries with them while dyanmically linked binaries dynamically load libraries at runtime from other files. Statically linked files are obviously larger.

`readelf -h /root/bin/hello`{{execute}}

## Scripts
Scripts are essentially text files which start with `#! /path/to/interpreter`. The Kernel executes the interpreter with the file name as the first argument and passestthe rest of the command arguments after. E.g. `./script.py -v` would cause the kernel to exec `/usr/bin/python3 ./script.py -v` (assuming `#! /usr/bin/python3` is the first line). When using the shell to execute a file, if the `#!` line is missing the shell will try to run the file as a shell script.

Create and execute a python or shell script file (don't forget to `chmod +x`)

## Statically linked files
Statically compile `hello.c`
`gcc -o hello-static -static hello.c`{{execute}}
Check the file type of the new binary
`file hello-static`{{execute}}
What is the size of the new binary? compare with the dynamically linked version
`ls -lh hello-static /root/bin/hello`{{execute}}

## Dynamically linked executables, the linker and libraries
To see what libraries a dynamically linked library requires, use the `ldd` command
`ldd /root/bin/hello`{{execute}}
Let's have a look at more executables
`ldd /usr/sbin/sshd`{{execute}}
The `ldd` command shows a list of _symbols_ and which library provides them. But how are symbols resolved? how are libraries found? This is the job of the _linker_. The [linker](https://linux.die.net/man/8/ld-linux.so) scans specific directories where libraries are installed and reads each library to see what symbols it provides. Binaries can also refer to specific libraries by path, and the user can provide additonal search path with the `LD_LIBRARY_PATH` environment variables.
Reading many library files takes time, which is why the linker builds a cached index ahead of time. This is done using the [`ldconfig`](https://linux.die.net/man/8/ldconfig) - usually invoked by package managers, but you may need invoke it youself when manually installing libraries. The main configuration file of the linker is `/etc/ld.so.conf`, have a look at it!
