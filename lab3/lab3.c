#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define COUNT_PARAM 5
#define COUNT_THREAD 4

//  https://docs.oracle.com/cd/E26502_01/html/E35303/docinfo.html#scrolltoc

void *printFunction(void *threadData) {
  fprintf(stderr, "%s\n", (char *)threadData);
  pthread_exit(NULL);
}

void printCreateThreadError() {
  if (errno == EAGAIN) {
    perror("Insufficient resources to create another thread\n");
  }
  if (errno == EAGAIN) {
    perror("A system-imposed limit on the number of threads was encountered\n");
  }
  if (errno == EINVAL) {
    perror("Invalid settings in attr\n");
  }
  if (errno == EPERM) {
    perror("No permission to set the scheduling policy and parameters "
           "specified in attr\n");
  }
}

void printJoinThreadError() {
  if (errno == EDEADLK) {
    perror("A deadlock was detected\n");
  }
  if (errno == EINVAL) {
    perror("thread is not a joinable thread\n");
  }
  if (errno == ESRCH) {
    perror("No thread with the ID thread could be found\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc != COUNT_PARAM) {
    perror("Invalid argument");
    return EXIT_FAILURE;
  }

  pthread_t thread[4];
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  for (int i = 0; i < COUNT_THREADS; ++i) {
    if (pthread_create(&thread[i], &attr, printFunction, (void *)argv[i])) {
      printCreateThreadError();
      pthread_attr_destroy(&attr);
      free(message);
      return EXIT_FAILURE;
    }

    if (pthread_join(thread[i], NULL)) {
      printJoinThreadError(); // or perror("pthread_join error")
      return EXIT_FAILURE;
    }
  }

  pthread_attr_destroy(&attr);
  free(message);
}
