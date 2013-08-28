#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "hello world";

int main(){
  int res;
  pthread_t a_thread;
  void *thread_result;

  res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
  if (res != 0) {
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }

  printf("Waiting for thread to finish ..\n");
  // pthread_join()函数，以阻塞的方式等待thread指定的线程结束。
  // 当函数返回时，被等待线程的资源被收回。如果进程已经结束，那么该函数会立即返回。并且thread指定的线程必须是joinable的。
  
  // 一个线程不能被多个线程等待，也就是说对一个线程只能调用一次pthread_join，否则只有一个能正确返回，其他的将返回ESRCH 错误
  
  // 代码中如果没有pthread_join主线程会很快结束从而使整个进程结束，从而使创建的线程没有机会开始执行就结束了。
  // 加入pthread_join后，主线程会一直等待直到等待的线程结束自己才结束，使创建的线程有机会执行。
  res = pthread_join(a_thread, &thread_result);
  if (res != 0){
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }

  printf("Thread joined, it returned %s\n", (char *)thread_result);
  printf("Message is now %s\n", message);
  exit(EXIT_FAILURE); 
}

// 新线程从这里开始执行
void *thread_function(void *arg){
  printf("Thread_function is running. Argument was %s\n", (char *)arg);
  sleep(3);
  printf("Message is changed by new thread..\n");
  // 更新全局变量
  // 修改数组message,main线程也可以访问数组
  strcpy(message, "Bye!");
  // 线程的结束有两种途径
  //   函数结束了，调用它的线程也就结束了
  //   另一种方式是通过函数pthread_exit来实现
  pthread_exit("Thank you for the CPU time");
}
