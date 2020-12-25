# Environment variables
Environment variables are part of the process attributes. The _fork_ call creates a copy of the original process so it has the same environment variables as the parent. When calling _exec_ however, the environment variables may be reset depending on the variant of the `exec(3)` call used.

Environment variables are a way to give the process information about its environment, including configurations data. Some environment variables are standard and are usually handled by _libc_, e.g. localization variables like `LC_ALL` and `LANG`. Others are custom and are interpreted arbitrarily.

Try running the `env` command to modify the environment of a process:
`env VAR=test /root/bin/hello`{{execute}}

Try the same using `export` (the shell builtin to define environment variables):
```
export VAR=test
/root/bin/hello
```{{execute}}

Edit the `fork_exec.py` file and modify the exec call to use the `execve()` call which allows resetting the environment variables vector:
```python
os.execve("/root/bin/hello", ["hello"], {"VARNAME": "value"})
```
Then run `./fork_exec.py`{{execute}}

## The default environment
Linux distributions have various ways of setting default environment variables. The biggest difference is between login/interactive sessions (e.g. when you login using SSH) and daemons/services. For example, [`pam_env`](https://man7.org/linux/man-pages/man8/pam_env.8.html) is often used for login sessions and when a shell is started it may export variables in `.profile`, `.bashrc` etc. For systems using _systemd_, daemons have their environment [defined in the unit files](https://coreos.com/os/docs/latest/using-environment-variables-in-systemd-units.html) either directly or by referring to an environment file.