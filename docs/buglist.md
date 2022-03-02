| RTOS Versions | Module                                   | Operation                            | Vulnerability            |
|---------------|------------------------------------------|--------------------------------------|--------------------------|
| 3.10-release  | net/core/dev.c                           | dev\_remove\_pack                    | NULL ptr deref           |
|               | arch/x86/kernel/cpu/perf\_event\_intel.c | intel\_shared\_reg\_put\_constraints | NULL prt deref           |
| 5.0-release   | include/linux/rbtree.h                   | rb\_insert\_color\_cached()          | general protection fault |
|               | fs/dcache.c                              | list\_lru\_add()                     | NULL prt deref           |
|               | fs/debugfs/file.c                        | debugfs\_remove()                    | use after free           |
| 5.4-release   | kernels                                  | swapgs\_restore\_regs()              | stack overflow           |
|               | kernel/relay.c                           | relay\_alloc\_buf()                  | deadlock                 |
|               | drivers/vt\_ioctl.c                      | vt\_ioctl()                          | general protection fault |
|               | fs/proc/proc\_sysctl.c                   | count\_subheaders()                  | general protection fault |
| 5.9-release   | driver/tty/vt/vt.c                       | vc\_con\_write\_normal()             | use after free           |
|               | include/linux/mm.h                       | vma\_interval\_tree\_iter\_next()    | general protection fault |
|               | drivers/video/console/vgacon.c           | clear\_buffer\_attributes()          | use after free           |
|               | lib/vsprintf.c                           | vsnprintf()                          | Bad page map             |
|               | mm/interval\_tree.c                      | anon\_vma\_interval\_tree\_insert()  | NULL prt deref           |
|               | kernel/sched/swait.c                     | swake\_up\_all\_locked()             | possible system lock     |
|               | drivers/tty/vt/vt.c                      | complement\_pos()                    | use after free           |
| 5.6-ktsan     | mm/slub.c                                | freelist\_dereference()              | stack segment fault      |
|               | lib/find\_bit.c                          | find\_next\_and\_bit()               | general protection fault |
|               | lib/idr.c                                | idr\_get\_free()                     | general protection fault |
|               | net/ipv4/route.c                         | ipv4\_dst\_check()                   | general protection fault |
|               | net/ipv6/addrlabel.c                     | ip6addrlbl\_net\_exit()              | general protection fault |
|               | fs/kernfs/file.c                         | kernfs\_notify\_workfn()             | general protection fault |
|               | mm/slub.c                                | \_\_kmalloc()                        | general protection fault |
|               | mm/slub.c                                | kmem\_cache\_alloc()                 | general protection fault |
|               | mm/shmem.c                               | shmem\_file\_read\_iter()            | rcu detected stall       |
|               | fs/proc/proc\_sysctl.c                   | unregister\_sysctl\_table()          | stack segment fault      |
|               | security/selinux/avc.c                   | avc\_node\_delete()                  | stack segment fault      |
