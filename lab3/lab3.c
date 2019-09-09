#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//  https://docs.oracle.com/cd/E26502_01/html/E35303/docinfo.html#scrolltoc

void *printFunction(void *threadData) {
  fprintf(stderr, "%s\n", (char *)threadData);
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

void printJoinThreadError() {
  if (errno == EDEADLK) {
    fprintf(stderr, "A deadlock was detected\n");
  }
  if (errno == EINVAL) {
    fprintf(stderr, "thread is not a joinable thread\n");
  }
  if (errno == ESRCH) {
    fprintf(stderr, "No thread with the ID thread could be found\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "invalid argument\n");
    exit(EXIT_FAILURE);
  }

  char **message = calloc(4, sizeof(char *));

  for (int i = 0; i < 4; ++i) {
    message[i] = argv[i + 1];
  }

  pthread_t thread[4];
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  for (int i = 0; i < 4; ++i) {
    if (pthread_create(&thread[i], &attr, printFunction, (void *)message[i])) {
      printCreateThreadError();
      pthread_attr_destroy(&attr);
      free(message);
      exit(EXIT_FAILURE);
    }

    if (pthread_join(thread[i], NULL)) {
      printJoinThreadError();
      exit(EXIT_FAILURE);
    }
  }

  pthread_attr_destroy(&attr);
  free(message);
}
