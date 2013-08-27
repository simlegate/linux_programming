#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

// 一个进程，主要包含三个元素：
//   一个可以执行的程序；
//   和该进程相关联的全部数据（包括变量，内存空间，缓冲区等等）
//   程序的执行上下文（execution context）

// 一个称为“程序计数器（program counter, pc）”的寄存器，指出当前占用 CPU的进程要执行的下一条指令的位置 

// 当分给某个进程的 CPU时间已经用完，操作系统将该进程相关的寄存器的值，保存到该进程在进程表中对应的表项里面；
// 把将要接替这个进程占用 CPU的那个进程的上下文，从进程表中读出，并更新相应的寄存器（这个过程称为“上下文交换(process context switch)”，
// 实际的上下文交换需要涉及到更多的数据，那和fork无关，不再多说，主要要记住程序寄存器pc指出程序当前已经执行到哪里，是进程上下文的重要内容,
// 换出 CPU的进程要保存这个寄存器的值，换入CPU的进程，也要根据进程表中保存的本进程执行上下文信息，更新这个寄存器）。 

// pid=fork(); 
// 操作系统创建一个新的进程（子进程），并且在进程表中相应为它建立一个新的表项。
// 新进程和原有进程的可执行程序是同一个程序；上下文和数据，绝大部分就是原进程（父进程）的拷贝，但它们是两个相互独立的进程！
// 此时程序寄存器pc，在父、子进程的上下文中都声称，这个进程目前执行到fork调用即将返回（此时子进程不占有CPU，子进程的pc不是真正保存在寄存器中，而是作为进程上下文保存在进程表中的对应表项内）

int main(){
  pid_t pid;
  char *message;
  int n;

  printf("fork programs starting\n");
  // return PID 父进程.fork()
  // return 0   子进程.fork()
  // reutrn -1  fork failed
  pid = fork();

  switch(pid){
    case -1:
      perror("fork failed!");
    case 0:
      message = "This is the child";
      n = 5;
      break;
    default:
      message = "This is the parent";
      n = 3;
      break;
  }

  // 父进程先结束，不会等待子进程结束
  for(; n > 0; n--){
    puts(message);
    sleep(1);
  }

  exit(0);
}
