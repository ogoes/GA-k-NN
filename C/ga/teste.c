#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>



void * compute(void * args) {
  void ** arg = (void **) args;
  int * primeiro = (int *) arg[0];
  printf("%i\n", *primeiro);
  char * charac = (char*) arg[2];
  printf("%s\n", charac);
}


int main () {
  pthread_t threads[1];
  int a = 0;
  int * b = (int *) malloc(sizeof(int));
  char * name = "asdasdas";

  for (int i = 0; i < 1; ++i) {
    void ** params = calloc(3, sizeof(void));
    params[0] = (void*) &a;
    params[1] = (void*) b;
    params[2] = (void*) name;
    pthread_create(&threads[i], NULL, compute, (void*) params);
  }
  for (int i = 0; i < 1; ++i) {
    pthread_join(threads[i], NULL);
  }
}
