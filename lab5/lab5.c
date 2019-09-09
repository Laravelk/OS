#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep for solaris

/*
http://citforum.ru/programming/unix/threads_2/
http://parallels.nsu.ru/WackoWiki/KursOperacionnyeSistemy/PraktikumPosixThreads/PthreadLectures/CreateExit#h177-4
https://www.opennet.ru/man.shtml?topic=pthread_setcancelstate&category=3&russian=4
https://code.woboq.org/userspace/glibc/nptl/pthread_setcancelstate.c.html source
http://man7.org/linux/man-pages/man3/pthread_cleanup_push.3.html source
*/

void printThreadEnd(void *arg) {
  free(arg);
  fprintf(stderr, "Thread end\n");
}

void *printFunction(void *threadData) {
  void *mem;
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  mem = malloc(1024);
  pthread_cleanup_push(printThreadEnd, mem);
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  fprintf(stderr, "Hello world\n");
  pthread_cleanup_pop(1);
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
    fprintf(stderr,
            "No permission to set the scheduling policy and parameters\n");
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
