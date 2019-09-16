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
// https://docs.oracle.com/cd/E26502_01/html/E35303/docinfo.html#scrolltoc

void *threadFunc(void *thread_data) {
  for (int i = 0; i < 10; ++i) {
    fprintf(stderr, "hello world in thread\n");
  }
  pthread_exit(NULL);
}

void printCreateThreadError() {
  if (errno == EAGAIN) {
    fprintf(
        stderr,
        "A system-imposed limit on the number of threads was encountered\n");
  }
  if (errno == EINVAL) {
    fprintf(stderr, "Invalid settings in attr\n");
  }
  if (errno == EPERM) {
    fprintf(stderr, "No permission to set the scheduling policy and parameters "
                    "specified in attr\n");
  }
}

int main(int argc, char *argv[]) {
  void *threadData = NULL;
  pthread_t thread;

  for (int i = 0; i < 10; ++i) {
    printf("hello world in main thread\n");
  }

  if (pthread_create(&thread, NULL, threadFunc, threadData)) {
    printCreateThreadError();
    exit(EXIT_FAILURE);
  }

  pthread_exit(NULL);
  return 0; // it's important
}
