## linux进程间通信--共享内存 ##（未完待续）
**（一）什么是共享内存**
> 共享内存是在两个正在运行的进程之间传递数据的一种非常有效的方式。共享内存的具体实现是不同进程共享的内存安排为同一段物理地址。共享内存是最高效的IPC 机制，因为他不涉及进程之间的任何数据传输。这种高效率带来的问题是，我们必须借用其他的辅助方法来同步进程间对共享内存的访问，否则会产生静态条件，因此，共享内存一般会和其他进程间通信一起使用。具体信息可通过“ [https://blog.csdn.net/ypt523/article/details/79958188](https://blog.csdn.net/ypt523/article/details/79958188) ”了解；

**（二）共享内存的使用**
   
linux共享内存的API都定义在sys/shm.h头文件中，包括4个系统调用：shmget、shmat、shmdt和shmctl，下面进行分节描述：

- 2.1 shmget系统调用

shmget系统调用创建一段新的共享内存，或者获取一段已经存在的共享内存，其定义如下：

#include <sys/shm.h>
   
int shmget(key_t key, size_t size, int shmflg);

【参数key】和semget系统调用一样，key参数是一个键值，它有效地为共享内存段命名，shmget函数成功时返回一个与key相关的共享内存标识符（非负整数），用于后续的共享内存函数。调用失败返回-1。不相关的进程可以通过该函数的返回值访问同一共享内存，它代表程序可能要使用的某个资源，程序对所有共享内存的访问都是间接的，程序先通过调用shmget函数并提供一个键，再由系统生成一个相应的共享内存标识符（shmget函数的返回值），只有shmget函数才直接使用信号量键，所有其他的信号量函数使用由semget函数返回的信号量标识符。

【参数size】指定共享内存的大小，单位是字节。

【参数shmflg】和semget系统调用的sem_flag参数相同，有9个比特的权限标志；如果要创建新的共享内存，需要使用IPC_CREAT，IPC_EXCL，如果是已经存在的，可以使用IPC_CREAT或直接传0。。

【函数返回值】成功时返回一个新建或已经存在的的共享内存标识符，取决于shmflg的参数。失败返回-1并设置错误码。

- 2.2 shmat系统调用

共享内存被创建/获取之后，我们并不能立即访问它，而是需要先用shmat 函数将之关联到进程的地址空间中，函数定义如下：

#include <sys/shm.h>

void * shmat(int shmid, const void * shmaddr, int shmflg);

[参数shmid]：共享存储段的标识符。

[参数* shmaddr]：指定将共享内存关联到进程的那块地址空间，最终的效果会受到shmflg参数的可选标志SHM_RAND的影响，但推荐做法是将shmaddr 设置为NULL，则存储段连接到由内核选择的第一个可以地址上（由系统决定，可以确保代码的可移植性）

[参数shmflg]：有SHM_RND、SHM_REMAP、SHM_RDONLY、SHM_EXEC；具体含义参照《linux高性能服务器编程》252-253页详细了解；注意：若指定了SHM_RDONLY位，则以只读方式连接此段，否则以读写方式连接此段。

[返回值]：成功返回共享存储段的指针（虚拟地址），并且内核将使其与该共享存储段相关的shmid_ds结构中的shm_nattch计数器加1（类似于引用计数）

- 2.3 shmdt系统调用

 在使用完共享内存之后，我们需要使用shmdt函数将之从进程的地址空间中分离出来，函数定义如下：

#include <sys/shm.h>

int shmdt(const void *shmaddr);

[参数* shmaddr]：连接以后返回的地址。

[返回值]：成功返回0，并将shmid_ds结构体中的 shm_nattch计数器减1；出错返回-1。
 
- 2.4 shmctl系统调用

和信号量的semctl函数一样，用来控制共享内存，它的原型如下：

#include <sys/shm.h>

int shmctl(int shmid, int cmd, struct shmid_ds *buf);

[参数shmid]：共享存储段标识符。

[参数cmd]：指定的执行操作，设置为IPC_RMID时表示可以删除共享内存,详细参数了解参考《linux高性能服务器编程》251页。

[参数* buf]：设置为NULL即可。

[返回值]：成功返回0，失败返回-1。

**（三）代码演示**

见csdn

**（四）共享内存的优缺点**

优点：我们可以看到使用共享内存进行进程间的通信真的是非常方便，而且函数的接口也简单，数据的共享还使进程间的数据不用传送，而是直接访问内存，也加快了程序的效率。同时，它也不像匿名管道那样要求通信的进程有一定的父子关系。

缺点：共享内存没有提供同步的机制，这使得我们在使用共享内存进行进程间通信时，往往要借助其他的手段来进行进程间的同步工作。
  
  
参考文章：

https://blog.csdn.net/ypt523/article/details/79958188

https://blog.csdn.net/ljianhui/article/details/10253345

https://blog.csdn.net/qq_41727218/article/details/82772056

