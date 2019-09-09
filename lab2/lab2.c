#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
  @author Ivan Morozov 5.09.19
 */

// http://man7.org/linux/man-pages/man3/pthread_join.3.html
// http://rus-linux.net/MyLDP/algol/light-weight-processes-linux-threads.html
// http://parallels.nsu.ru/WackoWiki/KursOperacionnyeSistemy/PraktikumPosixThreads/PthreadLectures/Intro2#h174-2
// https://docs.oracle.com/cd/E26502_01/html/E35303/docinfo.html#scrolltoc

void *threadFunc() {
  for (int i = 0; i < 10; ++i) {
    fprintf(stdout, "Hello world in thread\n");
  }
  fprintf(stdout, "\n");
}

void printCreateThreadError() {
  if (errno == EAGAIN) {
    fprintf(stderr, "Insufficient resources to create another thread\n");
  }
  if (errno == EINVAL) {
    fprintf(stderr, "Invalid settings in attr\n");
  }
  if (errno == EPERM) {
    fprintf(stderr, "No permission to set the scheduling policy and parameters "
                    "specified in attr\n");
  }
}

void printJoinThreadError() {
  if (errno == EDEADLK) {
    fprintf(stderr, "A deadlock was detected\n");
  }
  if (errno == EINVAL) {
    fprintf(stderr, "thread is not a joinable thread\n");
  }
  if (errno == EINVAL) {
    fprintf(stderr,
            "Another thread is already waiting to join with this thread\n");
  }
  if (errno == ESRCH) {
    fprintf(stderr, "No thread with the ID thread could be found\n");
  }
}

int main(int argc, char *argv[]) {
  void *threadData = NULL;
  pthread_t thread;

  if (pthread_create(&thread, NULL, threadFunc, threadData)) {
    printCreateThreadError();
    exit(EXIT_FAILURE);
  }

  if (pthread_join(thread, NULL)) {
    printJoinThreadError();
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; ++i) {
    fprintf(stdout, "Hello world in main thread\n");
  }
}
