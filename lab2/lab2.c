#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
  @author Ivan Morozov 5.09.19
 */

// http://man7.org/linux/man-pages/man3/pthread_join.3.html
// http://rus-linux.net/MyLDP/algol/light-weight-processes-linux-threads.html
// http://parallels.nsu.ru/WackoWiki/KursOperacionnyeSistemy/PraktikumPosixThreads/PthreadLectures/Intro2#h174-2

void *threadFunc() {
  for (int i = 0; i < 10; ++i) {
    fprintf(stdout, "Hello world in thread\n");
  }
  fprintf(stdout, "\n");
}

int main(int argc, char *argv[]) {
  void *threadData = NULL;
  pthread_attr_t attr;
  pthread_t thread;
  pthread_attr_init(&attr);
  int iter1 = pthread_create(&thread, &attr, threadFunc, threadData);

  if (iter1) {
    fprintf(stderr, "thread don't create\n");
    exit(EXIT_FAILURE);
  }

  int iter2 = pthread_join(thread, NULL);
  if (iter2 != 0) {
    fprintf(stderr, "thread error. Number of ERROR: ");
    fprintf(stderr, "%d\n", iter2);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; ++i) {
    fprintf(stdout, "Hello world in main thread\n");
  }
}
