#include <errno.h>
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
    fprintf(stderr, "hello world in thread\n");
  }
  pthread_exit(NULL);
}

void printCreateThreadError() {
  if (errno == EAGAIN) {
    fprintf(stderr, "Insufficient resources to create another thread");
  }
  if (errno == EAGAIN) {
    fprintf(stderr,
            "A system-imposed limit on the number of threads was encountered");
  }
  if (errno == EINVAL) {
    fprintf(stderr, "Invalid settings in attr");
  }
  if (errno == EPERM) {
    fprintf(stderr, "No permission to set the scheduling policy and parameters "
                    "specified in attr");
  }
}

int main(int argc, char *argv[]) {
  void *threadData = NULL;
  pthread_t thread;
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  for (int i = 0; i < 10; ++i) {
    printf("hello world in main thread\n");
  }

  if (pthread_create(&thread, &attr, threadFunc, threadData)) {
    printCreateThreadError();
    exit(EXIT_FAILURE);
  }

  pthread_attr_destroy(&attr);

  pthread_exit(NULL);
}
