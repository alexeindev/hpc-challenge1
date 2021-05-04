#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int main()
{   
    long k, hits;
    long n = 100000000;
        srand((int)clock());

        for (k=hits=0 ; k<n ; ++k){
            double  x = (double)rand() / (double)RAND_MAX ;
            double  y = (double)rand() / (double)RAND_MAX ;
/* printf("x = %f y = %f", x, y); */
            if(x*x + y*y < 1.0){
                ++hits;
            }
        }
    

    double pi_approx = 4.0 * hits/ n;

    printf("hits %d result %f",hits,pi_approx);
/*     printf("Aproximation of pi after %d tosses %ld", n, pi_approx ); */
}