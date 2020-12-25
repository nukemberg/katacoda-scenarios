# The PATH
When the shell or any of the 'p' variants of exec is trying to execute an executable binary, it will look for the binary in the `PATH` environment variable.
The `PATH` variable is a semicolon separated list of directories in which to look for the binary.

For example, `PATH=/usr/bin:/bin` means that when we try to `execlp("hello", "hello", NULL)` _libc_ will search for the executables `/usr/bin/hello` and `/bin/hello`. The shell behaves similarly, so when executing using `system(3)` the `PATH` will be searched.

So far, our `fork_exec.py` used absolute path to execute the hello binary. Let's try using the `PATH`. Edit the `fork_exec.py`{{edit}} to use `execvp`:
```python
os.execvp("hello", ["hello"])
```
And execute `./fork_exec.py`{{execute}}
If it doesn't work, `echo $PATH`{{execute}} to see the current `PATH` variable value, and add `/root/bin` to it either using `env` or `export`: `export PATH=$PATH:/root/bin`{{execute}}

What about the current directory? it recommended not to include '.' (the current directory) in the `PATH` because it would point to different directories depending on where you are at the moment, causing you to execute binaries you never intended on running. Note that the non 'p' variants of the _exec()_ _libc_ call will not search the `PATH` but **will run executables from the current working directory**.

## Setting the default PATH
The `PATH` is set like any other environment variable, in the appropriate configuration file for a login/interactive session (usually shell init files) or systemd/init service configurations for daemons. 