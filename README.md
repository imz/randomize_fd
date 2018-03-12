Sometimes (to reproduce a bug) we want to force the use of different
file descriptors in a sequence of `open` or `socket` followed by
`close`, so that:

1. the new fd is different from the previous one,
2. and the previous one doesn't look like a valid descriptor anymore.

(Due to 2, `strace -e inject=close:retval=0` is not a solution; though
it is a quick solution for 1 until we run out of the available number
of fds.)

Here, we solve this problem by providing wrappers around `open` and
`socket` to be LD_PRELOADed.

Example (normal behavior; the same descriptor `3` is re-used):

    $ strace -e trace=open,read -y -f cat /etc/altlinux-release /etc/redhat-release 2>&1 | tail -9
    open("/etc/altlinux-release", O_RDONLY) = 3</etc/altlinux-release>
    read(3</etc/altlinux-release>, "Simply Linux 7.0.5  (Dory)\n", 131072) = 27
    Simply Linux 7.0.5  (Dory)
    read(3</etc/altlinux-release>, "", 131072) = 0
    open("/etc/redhat-release", O_RDONLY)   = 3</etc/altlinux-release>
    read(3</etc/altlinux-release>, "Simply Linux 7.0.5  (Dory)\n", 131072) = 27
    Simply Linux 7.0.5  (Dory)
    read(3</etc/altlinux-release>, "", 131072) = 0
    +++ exited with 0 +++

Example (with our intervention, different descriptors are used):

    $ strace -e trace=open,read -y -f -E LD_PRELOAD=./randomize_fd_open.so cat /etc/altlinux-release /etc/redhat-release 2>&1 | tail -9
    open("/etc/altlinux-release", O_RDONLY) = 3</etc/altlinux-release>
    read(9</etc/altlinux-release>, "Simply Linux 7.0.5  (Dory)\n", 131072) = 27
    Simply Linux 7.0.5  (Dory)
    read(9</etc/altlinux-release>, "", 131072) = 0
    open("/etc/redhat-release", O_RDONLY)   = 3</etc/altlinux-release>
    read(15</etc/altlinux-release>, "Simply Linux 7.0.5  (Dory)\n", 131072) = 27
    Simply Linux 7.0.5  (Dory)
    read(15</etc/altlinux-release>, "", 131072) = 0
    +++ exited with 0 +++

## URL

* <http://git.altlinux.org/people/imz/packages/randomize_fd.git>
* <https://github.com/imz/randomize_fd>
