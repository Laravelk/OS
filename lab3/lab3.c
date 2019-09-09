#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *printFunction(void *threadData) {
  fprintf(stderr, "%s\n", (char *)threadData);
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
  thread_exit(NULL);
}

void printJoinThreadError() {
  if (errno == EDEADLK) {
    fprintf(stderr, "A deadlock was detected");
  }
  if (errno == EINVAL) {
    fprintf(stderr, "thread is not a joinable thread");
  }
  if (errno == ESRCH) {
    fprintf(stderr, "No thread with the ID thread could be found");
  }
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "invalid argument");
    exit(EXIT_FAILURE);
  }

  char **message = calloc(4, sizeof(char *));

  message[0] = argv[1];
  message[1] = argv[2];
  message[2] = argv[3];
  message[3] = argv[4];

  pthread_t thread[4];
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  for (int i = 0; i < 4; ++i) {
    if (pthread_create(&thread[i], &attr, printFunction, (void *)message[i])) {
      printCreateThreadError();
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
