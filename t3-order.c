/*
 * See the random order of execution
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void *print_message_function( void *ptr );
#define MAX_NUM_THREADS 10
int main()
{
    pthread_t threads[MAX_NUM_THREADS];
    char *message = "Thread X";
    int iret;
    void *retval;
    int args[MAX_NUM_THREADS];
    pthread_attr_t *attr1 = NULL, *attr2 = NULL;

    /* Create independent threads each of which will execute function */
    for(int i = 0; i < MAX_NUM_THREADS; i++){
        args[i] = '0' + i;
        iret = pthread_create(&threads[i], attr1, print_message_function, &args[i]);
        if (iret != 0){
            perror("pthread_create: ");
            exit(-1);
        }
    }

    /* Wait till threads are complete before main continues. */
    for(int i = 0; i < MAX_NUM_THREADS; i++){
        iret = pthread_join(threads[i], &retval);
        if (iret != 0){
            perror("pthread_join: ");
            exit(-1);
        }
        printf("Thread %d returns: %s\n",threads[i], (char*)retval);
    }
    
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