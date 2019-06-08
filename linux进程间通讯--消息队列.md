## linux进程间通讯--消息队列 ##
<font color = red>**（一）什么是消息队列** </font>

&ensp;&ensp;&ensp;&ensp;消息队列提供了一个进程给另外一个进程发送数据块的方法，每个数据块都可以被认为是由自己的类型的，接受者接受的数据块可以有不同的类型；不像管道和命名管道那样，必须以先进先出的方式接收数据。

&ensp;&ensp;&ensp;&ensp;同管道类似的是，他有一个不足的地方就是每个消息的最大长度是有上限的（**MSGMAX**），每个仙子队列的总的字节数（**MSGMNB**），系统上消息队列的总数上限（**MSGMNI**），可以用**cat/proc/sys/kernel/msgmax**查看具体的数据。

<font color = red>**（二）消息队列的使用** </font>

&ensp;&ensp;&ensp;&ensp;linux消息队列的API都定义在**sys/msg.h**头文件中，其中包括四个系统调用：msgget、msgsnd、msgrcv、msgctl；

<font color = Darkblue>**2.1 msgget系统调用** </font>

 &ensp;&ensp;&ensp;&ensp;用来创建一个消息队列，或者获取一个已存在的消息队列，定义如下：
    
	#include <sys/msg.h>
    int msgget(key_t, key, int msgflg);
     
    【参数 key】：键值，用来标识一个全局唯一的消息队列。
     
    【参数 msgflg】：一个权限标志，表示消息队列的访问权限，它与文件的访问权限一样。msgflg可以与IPC_CREAT做或操作，表示当key所命名的消息队列不存在时创建一个消息队列，如果key所命名的消息队列存时，IPC_CREAT标志会被忽略，而只返回一个标识符。
     
    【函数返回值】成功返回一个以key命名的消息队列的标识符（非零整数），失败时返回-1.

&ensp;&ensp;&ensp;&ensp;在shmget用于创建内存，与之关联的内核数据结构shmid_ds将被创建并初始化，shmid_ds结构体的定义和初始化参照《linux高性能服务器编程》263页了解。

<font color = Darkblue>**2.2 msgsnd系统调用** </font>

&ensp;&ensp;&ensp;&ensp;用来将一条信息添加到消息队列中，定义如下：

    #include <sys/msg.h>
    int msgsend(int msgid, const void *msg_ptr, size_t msg_sz, int msgflg);
     
    【参数 msgid】：是由msgget系统调用返回的消息队列标识符。
     
    【参数 msg_ptr】：指向一个准备发送消息的指针，消息必须被定义为如下：
     
        struct my_message
        {
            long int message_type;  /* 消息类型，必须是一个正整数 */
            char mtext[512]; /* 消息数据 */       
        };
     
    【参数 msg_sz】：是指消息的数据部分（mtext）的长度，这个长度可以为0，代表没有数据。
     
    【参数 msgflg】：控制msgsnd的行为。它通常仅支持IPC_NOWAIT标志，即以非阻塞的方式发送消息。默认情况下，发送消息时如果消息队列满了，则msgsnd将会阻塞。若IPC_NOWAIT标志被指定，则msgsnd将会立即返回并设置werrno为EAGAIN.具体情况参照《linux高性能服务器编程》264页。
     
    【函数返回值】：如果调用成功，消息数据的一分副本将被放到消息队列中，并返回0，失败时返回-1并设置errno.成功后回修改内核数据结构msqid_ds的部分字段。

<font color = Darkblue>**2.3 msgrcv系统调用** </font>

&ensp;&ensp;&ensp;&ensp;用来从消息队列中获取消息，定义如下:

    #include <sys/msg.h>
    int msgrcv(int msgid, void *msg_ptr, size_t msg_st, long int msgtype, int msgflg);
     
    【参数 msgtype】：指定接受哪一种类型的消息。可以实现一种简单的接收优先级。如果msgtype为0，就获取队列中的第一个消息。如果它的值大于零，将获取具有相同消息类型的第一个信息。如果它小于零，就获取类型等于或小于msgtype的绝对值的第一个消息。
     
    【参数 msgflg】：用于控制当队列中没有相应类型的消息可以接收时将发生的事情。
     
    【函数返回值】：调用成功时，该函数返回放到接收缓存区中的字节数，消息被复制到由msg_ptr指向的用户分配的缓存区中，然后删除消息队列中的对应消息。失败时返回-1.
     
     参数msgid, msg_ptr, msg_st的作用和函数msgsnd的参数意义相同一。

<font color = Darkblue>**2.4 msgctl系统调用** </font>

&ensp;&ensp;&ensp;&ensp;用来控制消息队列的某些属性，定义如下：

    #include <sys/msg.h>
    int msgctl(int msgid, int command, struct msgid_ds *buf);
     
    【参数 id】：同上。
     
    【参数 command】：command是将要采取的动作，它可以取6个值，这里列举常用的3个：
    （1）IPC_STAT：把msgid_ds结构中的数据设置为消息队列的当前关联值，即用消息队列的当前关联值覆盖msgid_ds的值。
    （2）IPC_SET：如果进程有足够的权限，就把消息列队的当前关联值设置为msgid_ds结构中给出的值
    （3）IPC_RMID：删除消息队列
     
    【参数 buf】：是指向msgid_ds结构的指针，它指向消息队列模式和访问权限的结构。msgid_ds结构至少包括以下成员：
    struct msgid_ds
    {
    uid_t shm_perm.uid;
    uid_t shm_perm.gid;
    mode_t shm_perm.mode;
    };
     
    【函数返回值】：成功时返回0，失败时返回-1.

<font color = red>**（三）代码演示**</font>

&ensp;&ensp;&ensp;&ensp;消息队列可以让不相关的进程进行行通信，所以我们在这里将会编写两个程序，msgreceive和msgsned来表示接收和发送信息。根据正常的情况，我们允许两个程序都可以创建消息，但只有接收者在接收完最后一个消息之后，它才把它删除。

<font color = green >接受数据源代码：recv.c </font>

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/msg.h>
     
    struct msg_st
    {
    	long int msg_type;
    	char text[BUFSIZ];
    };
     
    int main()
    {
    	int running = 1;
    	int msgid = -1;
    	struct msg_st data;
    	long int msgtype = 0; //注意1
     
    	//建立消息队列
    	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    	if(msgid == -1)
    	{
    		fprintf(stderr, "msgget failed with error: %d\n", errno);
    		exit(EXIT_FAILURE);
    	}
    	//从队列中获取消息，直到遇到end消息为止
    	while(running)
    	{
    		if(msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1)
    		{
    			fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
    			exit(EXIT_FAILURE);
    		}
    		printf("You wrote: %s\n",data.text);
    		//遇到end结束
    		if(strncmp(data.text, "end", 3) == 0)
    			running = 0;
    	}
    	//删除消息队列
    	if(msgctl(msgid, IPC_RMID, 0) == -1)
    	{
    		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
    		exit(EXIT_FAILURE);
    	}
    	exit(EXIT_SUCCESS);
    }

<font color = green >发送数据源代码：write.c </font>

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/msg.h>
    #include <errno.h>
     
    #define MAX_TEXT 512
    struct msg_st
    {
    	long int msg_type;
    	char text[MAX_TEXT];
    };
     
    int main()
    {
    	int running = 1;
    	struct msg_st data;
    	char buffer[BUFSIZ];
    	int msgid = -1;
     
    	//建立消息队列
    	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    	if(msgid == -1)
    	{
    		fprintf(stderr, "msgget failed with error: %d\n", errno);
    		exit(EXIT_FAILURE);
    	}
     
    	//向消息队列中写消息，直到写入end
    	while(running)
    	{
    		//输入数据
    		printf("Enter some text: ");
    		fgets(buffer, BUFSIZ, stdin);
    		data.msg_type = 1;//注意2
    		strcpy(data.text, buffer);
    		//向队列发送数据
    		if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)
    		{
    			fprintf(stderr, "msgsnd failed\n");
    			exit(EXIT_FAILURE);
    		}
    		//输入end结束输入
    		if(strncmp(buffer, "end", 3) == 0)
    			running = 0;
    		sleep(1);
    	}
    	exit(EXIT_SUCCESS);
    }


<font color = red>**（四）消息队列与命名管道的比较**</font>

&ensp;&ensp;&ensp;&ensp;消息队列跟命名管道有不少的相同之处，通过与命名管道一样，消息队列进行通信的进程可以是不相关的进程，同时它们都是通过发送和接收的方式来传递数据的。在命名管道中，发送数据用write，接收数据用read，则在消息队列中，发送数据用msgsnd，接收数据用msgrcv。而且它们对每个数据都有一个最大长度的限制。

&ensp;&ensp;&ensp;&ensp;**与命名管道相比，消息队列的优势在于：**

> 1、消息队列也可以独立于发送和接收进程而存在，从而消除了在同步命名管道的打开和关闭时可能产生的困难。
> 
> 2、同时通过发送消息还可以避免命名管道的同步和阻塞问题，不需要由进程自己来提供同步方法。
> 
> 3、接收程序可以通过消息类型有选择地接收数据，而不是像命名管道中那样，只能默认地接收。
