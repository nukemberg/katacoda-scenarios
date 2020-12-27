The GNU/Linux is comprised of the Linux kernel and the GNU libraries and tools. One of the core libraries which is required by POSIX is _libc_ is provided by the _glibc_ project. There are Linux variants which use alternative _libc_ implementations such as _libmusl_ which has become popular in container distros. Executables can also ignore _libc_ and provide their own using static linking, or just talk to the kernel directly using system calls.

    ----------------
    | Kernel       |
    ----------------
    | libc (glibc) |
    ----------------
    | Executable   |
    ----------------

Many of the POSIX behaviors are provided by _libc_. This includes hostname resolving, time zone, locales. 

## Interlude - man sections
The `man` command shows you a manual of utilities, concepts and various API functions. Manuals are divided into [sections](https://www.man7.org/linux/man-pages/man7/man-pages.7.html), so when you see something like `fork(3)` this means the _fork_ function in section 3 of the manual - library calls (_libc_). Similarly, `clone(2)` means _clone_ function
in section 2 - system calls. Read the man documentation for more details.

# Process execution
The standard way to execute a new process in POSIX is fork/exec. When you type `ls -l /` in your shell, this is what happens:
```C
pid_t pid = fork();
if (pid == 0) {
    // child
    execlp("/bin/ls", "ls", "-", "/", NULL);
}
```
If you shell didn't _fork()_ before running _execlp()_, the current shell would terminate when `ls` finished because _exec_ call replaces the current process memory with the executable image of the new binary. _fork_ makes a new process (which is a copy of the parent), and _exec_ converts the process in which it was called to a new program. When _exec_ is called some process attributes are cleared and some are retained. In particular the environment variables are only reset when using the _e_ variants of _exec_, e.g. `execve()`, `execvpe()`, `execle()`. The process name attribute is reset to the first argument of the argument vector. 

The POSIX standard also requires that _/bin/sh_ is provided, and it can optionally be used to execute things. The `system(3)` call is also used to execute processes, and does fork/exec for you, but with a shell. It is equivalent to:
```C
pid_t pid = fork();
if (pid == 0) {
    execl("/bin/sh", "sh", "-c", command, NULL);
}
```

Let's explore how executable behave on Linux. The majority of exercises will use Python as the API is similar to C, but even if you don't know Python or C it shouldn't be a problem - just follow the instructions and comments and the files.

# Katacoda
Katacoda is the platform this course is running on, integrating the instructions with a VM instance. On the right side of the screen you will have a terminal tab and an IDE tab. The IDE is fully featured VSCode, but of course you can edit files with vim if you prefer.

Note that some code snippets are clickable (look for ⏎ icon) and will execute the command in the terminal when clicked on. 