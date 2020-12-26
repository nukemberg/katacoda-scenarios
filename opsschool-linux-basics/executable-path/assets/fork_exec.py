#!/usr/bin/python3
import os

def get_progname():
    with open("/proc/self/comm") as f:
        return f.read().strip()


# change the following line to use os.fork()
pid = 0 
if pid:
    print("[Parent] Child PID: {}".format(pid))
    print("[Parent] Program name: {}".format(get_progname()))
else: # child
    print("[Child] Parent PID: {}".format(os.getppid()))
    print("[Child] Program name: {}".format(get_progname()))
    # exec call
    # os.execv("/root/bin/hello", ["hello"])
    print("[Child] Finished")