## linux进程间通讯--管道 ##
（一）管道的概念

   1、管道的原理

  >   <1>管道是由内核管理的一个缓冲区，相当于我们放入内存中的一个纸条。
  >   
> <2>管道的一端连接一个进程的输出。这个进程会向管道中放入信息。
> 
> <3>管道的另一端连接一个进程的输入，这个进程取出被放入管道的信息。
> 
> <4>一个缓冲区不需要很大一般为4K大小，它被设计成为环形的数据结构使之成为一种单向的、先进先出的结构；将它把一个进程的输出和另一个进程的输入连接在一起，以便管道可以被循环利用。
> 
> <5>当管道中没有信息的话，从管道中读取的进程会等待，直到另一端的进程放入信息。
> 
> <6>当管道被放满信息的时候，尝试放入信息的进程会等待，直到另一端的进程取出信息。
> 
> <7>当两个进程都终结的时候，管道也自动消失。

   3、管道的局限性

> <1>数据自己读不能自己写
> 
> <2>数据一旦被读走，便不在管道中存在，不可反复读取
> 
> <3>由于管道采用半双工通信方式。因此，数据只能在一个方向上流动

   4、管道的分类
> 
> 匿名管道：
> 
>   主要用于父进程与子进程之间，或者两个兄弟进程之间。在linux系统中可以通过系统调用建立起一个单向的通信管道，且这种关系只能由父进程来建立。
> 
> 命名管道： 
> 
>    命名管道是建立在实际的磁盘介质或文件系统（而不是只存在于内存中）上有自己名字的文件，任何进程可以在任何时间通过文件名或路径名与该文件建立联系。为了实现命名管道，引入了一种新的文件类型——FIFO文件（遵循先进先出的原则）。
>    实现一个命名管道实际上就是实现一个FIFO文件。命名管道一旦建立，之后它的读、写以及关闭操作都与普通管道完全相同。虽然FIFO文件的inode节点在磁盘上，但是仅是一个节点而已，文件的数据还是存在于内存缓冲页面中，和普通管道相同。
> 
（二）代码演示

  1、匿名管道

管道创建：intpipe(int filedis[2])；

当一个管道建立时，它会创建两个文件描述符：

filedis[0] 用于读管道，
filedis[1] 用于写管道

   管道用于不同进程间通信。通常先创建一个管道，再通过fork函数创建一个子进程，该子进程会继承父进程所创建的管道

> 创建管道pipe
> 
> 读管道read
> 
> 写管道write
> 
> 关闭管道close

    #include<unistd.h>
    
    #include<sys/types.h>
    
    #include<errno.h>
    
    #include<stdio.h>
    
    #include<stdlib.h>
    
    
    int  main()
    
    {
    
    int pipe_fd[2];
    
    pid_t pid;
    
    char buf_r[100];
    
    char* p_wbuf;
    
    int r_num;
    
    memset(buf_r,0,sizeof(buf_r));
     
    
    if(pipe(pipe_fd)<0)  /*创建管道*/
    
    {
    
     printf("pipe createerror\n");
    
     return -1;
    
    }
    
       
    if((pid=fork())==0)  /*创建子进程 子进程 OR 父进程？*/
    
    {
    
     printf("\n");
    
     close(pipe_fd[1]);
    
     sleep(2); /*为什么要睡眠*/
    
     if((r_num=read(pipe_fd[0],buf_r,100))>0)
    
     {
    
     printf(   "%d numbers read from the pipe is%s\n",r_num,buf_r);
    
     }   
    
     close(pipe_fd[0]);
    
     exit(0);
    
    }
    
    else if(pid>0)
    
    {
    
     close(pipe_fd[0]);
    
     if(write(pipe_fd[1],"Hello",5)!=-1)
    
     printf("parent write1Hello!\n");
    
     if(write(pipe_fd[1],"Pipe",5)!=-1)
    
     printf("parent write2Pipe!\n");
    
     close(pipe_fd[1]);
    
     sleep(3);
    
     waitpid(pid,NULL,0); /*等待子进程结束*/
    
     exit(0);
    
    }
    
    return 0;
    
    }

管道通讯是单向的，有固定的读端和写端。

数据被进程从管道读出后，在管道中该数据就不存在了。

当进程去读取空管道的时候，进程会阻塞。

当进程往满管道写入数据时，进程会阻塞。

管道容量为64KB


    #define PIPE_BUFFERS 16

    #include/linux/pipe_fs_i.h）//必须在系统调用fork( )前调用pipe( )，否则子进程将不会继承文件描述符

  2、命名管道

#include <sys/types.h>

#include <sys/stat.h>

int mkfifo(const char * pathname, mode_tmode)

pathname：FIFO文件名

mode：属性（见文件操作章节）

一旦创建了一个FIFO，就可用open打开它，一般的文件访问函数（close、read、write等）都可用于FIFO

> （1）创建管道mkfifo
> 
> （2）打开管道open
> 
> （3）读管道read
> 
> （4）写管道write
> 
> （5）关闭管道close
> 
> （6）删除管道unlink

fifo_write.c

    #include<sys/types.h>
    
    #include<sys/stat.h>
    
    #include<errno.h>
    
    #include<fcntl.h>
    
    #include<stdio.h>
    
    #include<stdlib.h>
    
    #include<string.h>
    
    #defineFIFO_SERVER "/tmp/myfifo"
    
    
    int main(intargc,char** argv)
    
    {
    
      int fd;
    
      char w_buf[100];
    
      int nwrite; 
    
      /*打开管道*/
    
      fd=open(FIFO_SERVER,O_WRONLY|O_NONBLOCK,0);
    
    
      if(argc==1)
    
      {
    
       printf("Please sendsomething\n");
    
       exit(-1);
    
      }
    
      strcpy(w_buf,argv[1]);
    
    
      /* 向管道写入数据 */
    
      if((nwrite=write(fd,w_buf,100))==-1)
    
      {
    
    printf("The FIFO hasnot been read yet.Please try later\n");
    
      }
    
      else
    
       printf("write %s to theFIFO\n",w_buf);
    
    }

fifo_read.c

    #include<sys/types.h>
    
    #include<sys/stat.h>
    
    #include<errno.h>
    
    #include<fcntl.h>
    
    #include<stdio.h>
    
    #include<stdlib.h>
    
    #include<string.h>
    
    #define FIFO"/tmp/myfifo"
    
    
    int main(intargc,char** argv)
    
    {
    
      char buf_r[100];
    
      int  fd;
    
      int  nread;
    
    
      /* 创建管道 */
    
      if((mkfifo(FIFO,O_CREAT|O_EXCL)<0)&&(errno!=EEXIST))
    
       printf("cannot createfifoserver\n");
    
    
      printf("Preparing for readingbytes...\n");
    
    
      memset(buf_r,0,sizeof(buf_r));
    
    
      /* 打开管道 */
    
      fd=open(FIFO,O_RDONLY|O_NONBLOCK,0);
    
      if(fd==-1)
    
      {
    
       perror("open");
    
       exit(1);
    
      }
    
      while(1)
    
      {
    
       memset(buf_r,0,sizeof(buf_r));
     
    
       if((nread=read(fd,buf_r,100))==-1)
    
       {
    
       if(errno==EAGAIN)
    
       printf("no datayet\n");
    
       }
    
       printf("read %s fromFIFO\n",buf_r);
    
       sleep(1);
    
      }   
    
      pause(); /*暂停，等待信号*/
    
      unlink(FIFO); //删除文件
    
    }

FIFO文件在使用上和普通文件有相似之处，但是也有不同之处：

Ø  读取fifo文件的进程只能以”RDONLY”方式打开fifo文件。

Ø  写fifo文件的进程只能以”WRONLY”方式打开fifo
Ø  fifo文件里面的内容被读取后，就消失了。但是普通文件里面的内容读取后还存在。

（三）区别

3.1、无名管道:

 >  管道是半双工的，数据只能向一个方向流动；需要双方通信时，需要建立起两个管道；只能用于父子进程或者兄弟进程之间（具有亲缘关系的进程）。
> 
> 单独构成一种独立的文件系统：管道对于管道两端的进程而言，就是一个文件，但它不是普通的文件，它不属于某种文件系统，而是自立门户，单独构成一种文件系统，并且只存在与内存中。
> 
> 数据的读出和写入：一个进程向管道中写的内容被管道另一端的进程读出。写入的内容每次都添加在管道缓冲区的末尾，并且每次都是从缓冲区的头部读出数据。（有点像队列哈）
> 
>    该函数创建的管道的两端处于一个进程中间，在实际应用中没有太大意义，因此，一个进程在由 pipe()创建管道后，一般再fork一个子进程，然后通过管道实现父子进程间的通信（因此也不难推出，只要两个进程中存在亲缘关系，这里的亲缘关系指的是具有共同的祖先，都可以采用管道方式来进行通信）。
> 
>    向管道中写入数据时,linux将不保证写入的原子性，管道缓冲区一有空闲区域，写进程就会试图向管道写入数据。如果读进程不读走管道缓冲区中的数据，那么写操作将一直阻塞。
> 
注：只有在管道的读端存在时，向管道中写入数据才有意义。否则，向管道中写入数据的进程将收到内核传来的SIFPIPE信号，应用程序可以处理该信号，也可以忽略（默认动作则是应用程序终止）。

3.2、有名管道：

>  不同于管道之处在于它提供一个路径名与之关联，以FIFO的文件形式存在于文件系统中。这样，即使与FIFO的创建进程不存在亲缘关系的进程，只要可以访问该路径，就能够彼此通过FIFO相互通信（能够访问该路径的进程以及FIFO的创建进程之间），因此，通过FIFO不相关的进程也能交换数据。值得注意的是，FIFO严格遵循先进先出（first in first out），对管道及FIFO的读总是从开始处返回数据，对它们的写则把数据添加到末尾。它们不支持诸如lseek()等文件定位操作
> 
>   该函数的第一个参数是一个普通的路径名，也就是创建后FIFO的名字。第二个参数与打开普通文件的open()函数中的mode 参数相同。如果mkfifo的第一个参数是一个已经存在的路径名时，会返回EEXIST错误，所以一般典型的调用代码首先会检查是否返回该错误，如果确实返回该错误，那么只要调用打开FIFO的函数就可以了。一般文件的I/O函数都可以用于FIFO，如close、read、write等等

参考资料：

https://segmentfault.com/a/1190000009528245

https://blog.csdn.net/qq100440110/article/details/50902739

https://blog.csdn.net/zm1_1zm/article/details/52987310

https://blog.csdn.net/oguro/article/details/53841949


