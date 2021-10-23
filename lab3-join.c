#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *func3 (void *arg){
   int * ret = (int *)malloc(sizeof(int));

   *ret = 11;
   printf("In thread start routine\n");
   pthread_exit((void *) ret);
}

int main() {
   pthread_t thread_id;
   int * rptr;

   pthread_create(&thread_id, NULL, func3, NULL);
   pthread_join(thread_id, (void **) &rptr);
   printf("Thread has terminated with a return value of %d\n", *rptr);
   printf("Program ended.\n");
   return 0;
}

