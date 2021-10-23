/*
 * Zombie thread. Pthread_detach
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void *print_message_function( void *ptr );

int main()
{
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int  iret1, iret2;
    void *retval1, *retval2;
    pthread_attr_t *attr1 = NULL, *attr2 = NULL;

    /* Create independent threads each of which will execute function */

    iret1 = pthread_create(&thread1, attr1, print_message_function, (void*) message1);
    if (iret1 != 0){
        perror("pthread_create: ");
        exit(-1);
    }
    pthread_detach(thread2);
    iret2 = pthread_create(&thread2, attr2, print_message_function, (void*) message2);
    if (iret2 != 0){
        perror("pthread_create: ");
        exit(-1);
    }

    /* Wait till threads are complete before main continues. */
    
    // change1
    // pthread_join( thread1, &retval1);
    // pthread_join(thread2, &retval2); 

    printf("Thread %d returns: %s\n",thread1, (char*)retval1);
    printf("Thread %d returns: %s\n",thread2, (char*)retval2);
    return 0;
}

void *print_message_function( void *ptr )
{
    pthread_t threadA = pthread_self();
    pid_t pid = getpid();
    char *message;
    char *rtn = "I'm ok";
    message = (char *) ptr;
    printf("Thread:%d in Process %d get msg:%s \n", threadA, pid, message);
    
    pthread_exit(rtn);   
}