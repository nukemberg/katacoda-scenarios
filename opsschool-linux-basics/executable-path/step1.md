# Fork/exec
As explained in the intro, Unix systems use fork/exec to start new programs. To better understand how these calls behave let's try to use them directly.

Edit the `fork_exec.py` file so that it calls fork and displays the pid from both the parent and child (use Katacoda built-in vscode). After editing, run the program: `./fork_exec.py`{{execute}}

You should see something like this:
```
[Parent] Child PID: 864531
[Child] Parent PID: 864530
[Parent] Program name: python
[Child] Program name: python
[Child] Finished
```
Note how the output of the child and parent are interleaved as they are running in parallel on multiple CPUs. Try running on a single CPU using the [`taskset`](https://man7.org/linux/man-pages/man1/taskset.1.html) utility and see if there's a difference:
`taskset -c 0 ./fork_exec.py`{{execute}}

The fork call duplicates the process and returns twice: once in the parent and once in the child. The return value is different - the child PID in the parent and 0 in the child - so that we can distinguish between the processes in our program.

Let's proceed to use `exec(3)`. Change the file to exec the hello binary in the child process.
```
os.execvp("/usr/bin/hello", ["hello"])
```
And run `fork_exec.py` again. What happes now? Has the child printed the "Finished" line? Why?

What would happen if we removed the fork call and ran `execv()` only?
