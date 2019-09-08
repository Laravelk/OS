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
// http://man7.org/linux/man-pages/man3/pthread_detach.3.html

void *threadFunc(void *thread_data) {
  for (int i = 0; i < 10; ++i) {
    fprintf(stderr, "hello world in thread\n");
  }
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

void printDetachThreadError() {
  if (errno == EINVAL) {
    fprintf(stderr, "thread is not a joinable thread");
  }
  if (errno == ESRCH) {
    fprintf(stderr, "No thread with the ID thread could be found");
  }
}

int main(int argc, char *argv[]) {
  void *threadData = NULL;
  pthread_t thread;
  pthread_attr_t attr;
  pthread_attr_init(&attr); // default thread joinable

  /* pthread_attr_setdetachstate(&attr, null) -- returns the detach state
     attribute of the thread attributes object attr in the buffer pointed to by
       detachstate */

  if (pthread_create(&thread, &attr, threadFunc, threadData)) {
    printCreateThreadError();
    exit(EXIT_FAILURE);
  }

  if (pthread_detach(thread)) {
    printDetachThreadError();
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; ++i) {
    printf("hello world in main thread\n");
  }

  return 0;
}
