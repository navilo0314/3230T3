#include <stdio.h>
#include <pthread.h>

int x = 7;

// Add 33 to the global variable x
void *func1 (void *arg){
   
   x += 33;
   printf("\nf1: add 33 to x and becomes : %d\n", x);
   
   pthread_exit(NULL);
}

// Divide x by 10
void *func2 (void *arg){

   x /= 10;
   
   printf("\nf2: divide x by 10 and becomes : %d\n", x);   
   pthread_exit(NULL);
}

// subtract x by 2
void *func3 (void *arg){

   x -= 2;
   
   printf("\nf3: subtract x by 2 and becomes : %d\n", x);   
   pthread_exit(NULL);
}

// workload for dummy threads
void *dummy (void *arg) {
   int i, y=0;
   for (i=0; i<536870912; i++)
	y += 3;

   pthread_exit(NULL);
}

int main() {
   pthread_t thdummy, thread_id1, thread_id2, thread_id3;
   int j;

   //Create the threads.
   // These four dummy threads must be created first
   for (j=0; j< 4; j++)
   	pthread_create(&thdummy, NULL, dummy, NULL);
   // These are the worker threads for the computation
   pthread_create(&thread_id1, NULL, func1, NULL);
   pthread_create(&thread_id2, NULL, func2, NULL);
   pthread_create(&thread_id3, NULL, func3, NULL);


   //Wait for all threads terminate
   pthread_join(thread_id1, NULL);
   pthread_join(thread_id2, NULL);
   pthread_join(thread_id3, NULL);

   printf("\nFinal value of x is %d\n", x);
   
   return 0;
}
