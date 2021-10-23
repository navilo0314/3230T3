#include <stdio.h>
#include <pthread.h>

//Store the subrange of computation.
struct Range {
   int up;
   int down;
};

#define RANGE 10000

pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;
static volatile int sum = 0;

void *functionC(void* var)
{
	int i;
	//get the assigned range
	struct Range *SubRange = (struct Range*)var;
	//perform summation of this range
	for (i=SubRange->down;i<=SubRange->up;i++){
		// pthread_mutex_lock( &m_mutex );
		sum+=i;	
		// pthread_mutex_unlock( &m_mutex );
	}

	pthread_exit(NULL);
}

int main()
{
	int rc;
	pthread_t thread1, thread2, thread3, thread4;
	struct Range SubRange_1, SubRange_2, SubRange_3, SubRange_4;
	int range = RANGE/4;
	
	/* Create independent threads each of which will execute functionC */
	SubRange_1.up = range;
	SubRange_1.down = 1;
	if( (rc=pthread_create(&thread1, NULL, &functionC, (void *)&SubRange_1)) )
	   printf("Thread creation failed: %d\n", rc);
	
	SubRange_2.up = 2*range;
	SubRange_2.down = 1+range;	
	if( (rc=pthread_create(&thread2, NULL, &functionC, (void *)&SubRange_2 )) )
		printf("Thread creation failed: %d\n", rc);

	SubRange_3.up = 3*range;
	SubRange_3.down = 1+2*range;
	if( (rc=pthread_create(&thread3, NULL, &functionC, (void *)&SubRange_3)) )
	   printf("Thread creation failed: %d\n", rc);
	
	SubRange_4.up = RANGE;
	SubRange_4.down = 1+3*range;	
	if( (rc=pthread_create(&thread4, NULL, &functionC, (void *)&SubRange_4 )) )
		printf("Thread creation failed: %d\n", rc);
	
	/* Wait till threads are complete before main continues. */	
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL); 
	pthread_join( thread3, NULL);
	pthread_join( thread4, NULL); 
	
	printf("Sum of whole range: %d\n", sum);
	
	//Release mutex;
	pthread_mutex_destroy(&m_mutex);
	
	return 0;
}

