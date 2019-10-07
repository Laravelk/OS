#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define NUM_STEPS 5000
#define MAX_COUNT_THREADS 500
#define DEFAULT_COUNT_THREAD 10

/*
  @author Ivan Morozov
 */

/*
 *  https://www.opennet.ru/man.shtml?topic=strtoll&category=3&russian=0
 * http://parallels.nsu.ru/wiki/KursOperacionnyeSistemy/PraktikumPosixThreads/PthreadLectures/ThreadManagement/
 * http://parallels.nsu.ru/WackoWiki/KursOperacionnyeSistemy/PraktikumPosixThreads/PthreadLectures/Intro2#h174-2
 */

long long threadNum;

void printError(int code, char *error) {
  if (error == NULL) {
    error = "error occurred";
  }
  if (code != 0) {
    fprintf(stderr, "%s: %s\n", error, strerror(code));
    exit(1);
  }
}

typedef struct Params_t {
  int firstTermIdx;
  double partSum;
} Params;

void *calcPartSum(void *params) {
  Params *p = (Params *)params;
  double sum = 0;
  long long totalSteps = NUM_STEPS * threadNum;
  for (long long i = p->firstTermIdx; i < totalSteps; i += threadNum) {
    sum += 1.0 / (i * 4.0 + 1.0);
    sum -= 1.0 / (i * 4.0 + 3.0);
  }
  p->partSum = sum;
  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  int code;
  char *argEndPtr;

  if (argc > 1) {
    threadNum = DEFAULT_COUNT_THREAD;
  } else {
    threadNum = strtoll(argv[1], &argEndPtr, 0);
  }

  if ((argc > 1 && argEndPtr != '\0') || threadNum < 1 ||
      threadNum > MAX_COUNT_THREADS || argc > 2) {
    fprintf(stderr, "use %s thread. max count is %d", argv[0],
            MAX_COUNT_THREADS);
    return (EXIT_FAILURE);
  }

  double pi = 0;
  Params params[threadNum];
  pthread_t threads[threadNum];
  printf("calculate pi\n");
  for (int i = 0; i < threadNum; ++i) {
    params[i].firstTermIdx = i;
    code = pthread_create(&threads[i], NULL, calcPartSum, &params[i]);
    printError(code, "thread creation");
  }

  for (int i = 0; i < threadNum; ++i) {
    code = pthread_join(threads[i], NULL);
    printError(code, "thread joining");
    pi += params[i].partSum;
  }
  pi = pi * 4.0;

  printf("Done: pi = %.16g \n", pi);
  printf("Expected:  3.141592653589793\n");

  return (EXIT_SUCCESS);
}
