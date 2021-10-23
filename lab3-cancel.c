#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *func1 (void *arg){
   printf("func1 set the cancellation state to ignore\n");
   pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
   sleep(5);
   printf("func1 set the cancellation state to enable with immediate action\n");
   pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
   pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
   while (1) {
      sleep(1);
      printf("...");
   }
}

void *func2 (void *arg){
   int i;
   pthread_t tid = *(pthread_t *)arg;
   for (i=0; i<4; i++) {
      printf("func2 sends a cancellation request to func1\n");
      pthread_cancel(tid);
      sleep(2);
   }
   pthread_exit(NULL);
}

int main() {
   pthread_t thread_id1, thread_id2;

   pthread_create(&thread_id1, NULL, func1, NULL);
   sleep(2);
   pthread_create(&thread_id2, NULL, func2,(void*)&thread_id1);

   pthread_join(thread_id1, NULL);
   printf("func1 has terminated\n");
   pthread_join(thread_id2, NULL);
   printf("func2 has terminated\n");
   return 0;
}
