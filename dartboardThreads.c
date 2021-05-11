#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void * Dartboard(void * arg){
    long * numShots = (long *) arg;
    long k, hits;
        srand((int)clock());

        for (k=hits=0 ; k < * numShots ; ++k){
            double  x = (double)rand() / (double)RAND_MAX ;
            double  y = (double)rand() / (double)RAND_MAX ;
            if(x*x + y*y <= 1.0){
                ++hits;
            }
        }

    return (long *) hits;

} 

double threadFunction(long numShots){
    long range = numShots / NUM_THREADS;
    int offset = numShots % NUM_THREADS;  
    long offsetRange = range + offset;
    pthread_t workers[NUM_THREADS];
    long numHits[NUM_THREADS];
    long totalHits;

    for (int j=0 ; j < NUM_THREADS ; ++j){
        if(j == NUM_THREADS - 1){
            pthread_create(&workers[j], NULL, Dartboard, (void *)&offsetRange);
        }else{
            pthread_create(&workers[j], NULL, Dartboard, (void *)&range);
        }
        pthread_join(workers[j], &numHits[j]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
	{
        totalHits +=  numHits[i];
	}
    
    double pi_approx = 4.0 * totalHits/ numShots;

    return pi_approx;
    pthread_exit(0);

}


int main()
{   long n = 100000000;


    int iterations = 10;
    double sum = 0.0; 
    struct timespec begin, end;
    double results[10] = { 0.0 };
    
    clock_gettime(CLOCK_REALTIME, &begin);
    
    

    for (int i = 0 ; i < iterations ; ++i){
        results[i] = threadFunction(n);
    }

    for (int k = 0 ; k < iterations ; ++k){
        sum += results[k];
    }


    double mean_result = sum / iterations;

    clock_gettime(CLOCK_REALTIME, &end);

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;
    printf("%lf\n", elapsed);

}