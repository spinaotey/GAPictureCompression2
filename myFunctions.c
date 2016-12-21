#include "myFunctions.h"
#include <math.h>
#include <stdlib.h>

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
