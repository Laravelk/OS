#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep for solaris

// http://parallels.nsu.ru/WackoWiki/KursOperacionnyeSistemy/PraktikumPosixThreads/PthreadLectures/CreateExit#h177-4
// http://man7.org/linux/man-pages/man3/pthread_cancel.3.html

void *printFunction(void *threadData) {
  fprintf(stderr, "Hello world\n");
  pthread_exit(NULL);
}

void printCreateThreadError() {
  if (errno == EAGAIN) {
    fprintf(stderr, "Insufficient resources to create another thread\n");
  }
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

printCancleThreadError() {
  if (errno == ESRCH) {
    fprintf(stderr, "No thread with the ID thread could be found");
  }
}

int main(int argc, char *argv[]) {
  void *threadData = NULL;
  pthread_t thread;

  if (pthread_create(&thread, NULL, printFunction, threadData)) {
    printCreateThreadError();
    exit(EXIT_FAILURE);
  }

  sleep(2);

  if (pthread_cancel(thread)) {
    printCancleThreadError();
    exit(EXIT_FAILURE);
  }
}
