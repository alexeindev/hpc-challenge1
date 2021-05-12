#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4

double Dartboard(long numShots){

    long k, hits;
        srand((int)clock());
    #pragma omp parallel
    
        for (k=hits=0 ; k < numShots ; ++k){
            double  x = (double)rand() / (double)RAND_MAX ;
            double  y = (double)rand() / (double)RAND_MAX ;
            /* printf("x = %f y = %f", x, y); */
            if(x*x + y*y <= 1.0){
                ++hits;
            }
        }
    double pi_approx = 4.0 * hits/ numShots;
    return pi_approx;

} 

int main()
{   long n = 10000000;
    int iterations = 10;
    double sum = 0.0; 
    struct timespec begin, end;
    double results[10] = { 0.0 };
    
    clock_gettime(CLOCK_REALTIME, &begin);

    omp_set_num_threads(NUM_THREADS);


    for (int i = 0 ; i < iterations ; ++i){
        results[i] = Dartboard(n);
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