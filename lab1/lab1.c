#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
 @author Morozov Ivan 4.09.2019
 */

// http://rus-linux.net/MyLDP/algol/light-weight-processes-linux-threads.html
// http://parallels.nsu.ru/WackoWiki/KursOperacionnyeSistemy/PraktikumPosixThreads/PthreadLectures/Intro2#h174-2
// http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html

void *threadFunc(void *thread_data) {
  for (int i = 0; i < 10; ++i) {
    printf("hello world in thread\n");
  }
}

int main(int argc, char *argv[]) {
  void *threadData = NULL;
  pthread_t thread;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  int iter1 = pthread_create(&thread, &attr, threadFunc, threadData);
  if (iter1) {
    fprintf(stderr, "thread don't create\n");
    exit(EXIT_FAILURE);
  }

  if (!pthread_detach(
          thread)) // http://man7.org/linux/man-pages/man3/pthread_detach.3.html
  {
    fprintf(stderr, "bad end of thread");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; ++i) {
    printf("hello world in main thread\n");
  }

  return 0;
}
