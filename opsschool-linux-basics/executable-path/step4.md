# The executable bit
How does the kernel know that a file is executable? Every inode has attributes which define its permissions, and one of the [permission bits](https://en.wikipedia.org/wiki/Chmod) is the `execute` permission. To make a file executable we `chmod +x FILENAME`. Note that the executable permission can be assigned to the owner, group, others or all just like the read and write permissions. For example, `chmod 0700 FILENAME` uses mod mask to set the file permissions such that only the owner can read, write and execute the file.

Try to remove the executable bit of `/root/bin/hello` and see what happens when you execute it.
`chmod -x /root/bin/hello`{{execute}}

Now create a new file `test.sh` which contains a few shell commands: 
```
echo START
echo $0 # argument 0, the program name
echo DONE
```

Make it executable `chmod +x test.sh`{{execute}} and run it: `./test.sh`{{execute}}
Try executing is with _exec()_ in `fork_exec.py`. Is there a difference? Why?
