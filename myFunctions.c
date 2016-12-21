#include "myFunctions.h"
#include <math.h>
#include <stdlib.h>


/**************************************************************************
 *  RANDOM NUMBERS FUNCTION
 **************************************************************************/

/*  RANDUNIF_R
 *
 *  Returns random uniform number in [0,1) using a given seed.
 *
 *  Input:
 *      *seedp: pointer to seed which is modified.
 *
 *  Return: uniform number in [0,1).
 */
double randUnif_r(int *seedp){
    unsigned int m = RAND_MAX+1;
    return((double) rand_r(seedp)/(double) m);
}

/*  RANDSTDNORM_R
 *
 *  Returns random standard normal distributed number using a given
 *  seed. It uses Box-Mueller.
 *
 *  Input:
 *      *seedp: pointer to seed which is modified.
 *
 *  Return: standard normal distributed number.
 */
double randStdNorm_r(int *seedp){
    double u1,u2;
    u1 = randUnif_r(seedp);
    u2 = randUnif_r(seedp);
    return(sqrt(-2*log(u1))*cos(2*PI*u2));
}


/*  RANDNORM_R
 *
 *  Returns random normal distributed number using a given
 *  seed, mean and standard deviation.
 *
 *  Input:
 *      *seedp: pointer to seed which is modified.
 *      mean: mean of the distribution.
 *      sd: standard deviation of the distribution.
 *
 *  Return: standard normal distributed number.
 */
double randNorm_r(int *seedp, double mean, double sd){
    return(rndStdNorm_r(seedp)*sd+mean);
}

/**************************************************************************
 *  SORTING FUNCTIONS 
 **************************************************************************/


/*  MINMAXINT
 *
 *  Computes the minimum and maximum of an integer vector.
 *  
 *  Input:
 *      *v: pointer of the vector.
 *      n: length of the vector.
 *      *min: pointer to save minimum.
 *      *max: pointer to save maximum.
 */
void minMaxInt(int *v, int n, int *min, int *max){
    int i;
    *min = v[0];
    *max = v[0];
    for(i = 1; i<n; i++){
        if(v[i] < *min)
            *min = v[i];
        if(v[i] > *max)
            *max = v[i];
    }
}
