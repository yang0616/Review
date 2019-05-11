## 前言 ##
clone、fork、vfork三个系统调用的实现都是通过 do_ fork()实现的，不同的是对do_ fork()的调用参数。关键是这些参数起的作用；系统调用clone()的主要用途是创建一个线程，这个线程可以是内核线程，也可以是用户线程。创建用户控件线程时，可以给定子线程用户空间堆栈的位置，还可以指定子进程运行的起点。同时也可以用clone()创建进程，有选择的赋值父进程的资源；fork()是全面的复制父进程的资源创建进程；vfork()的作用的创建一个线程，主要作用只是为作为创建进程的中间步骤，目的在于提高创建时的效率，减少系统的开销；
## （一）do_fork()的函数原型 ##
    int do_ fork(unsigned long clone_flags, unsigned long stack_start,struct pt_regs *regs, unsigned long stack_size)；
    



