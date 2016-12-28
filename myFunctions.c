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
double randUnif_r(unsigned int *seedp){
    unsigned int m = (unsigned int)RAND_MAX + 1;
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
double randStdNorm_r(unsigned int *seedp){
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
double randNorm_r(unsigned int *seedp, double mean, double sd){
    return(randStdNorm_r(seedp)*sd+mean);
}

/*  RANDINT_R
 *
 *  Returns random integer from 0 to n-1.
 *
 *  Input:
 *      *seedp: pointer to seed which is modified.
 *      n: upper limit for integers (not included).
 *
 *  Return: random integer from 0 to n-1.
 */
int randInt_r(unsigned int *seedp, int n){
    return((int)floor(randUnif_r(seedp)*n));
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

/*  ARGSMINLONG
 *
 *  Finds the arguments of the nargs smalles values and stores those
 *  arguments in args.
 *  
 *  Input:
 *      *v: vector with values to find their arguments.
 *      nv: length of v.
 *      args: vector to store arguments in order.
 *      nargs: number of arguments to store in args.
 */
void argsMinLong(long *v, int nv, int *args, int nargs){
    int i,j,k;
    args[0] = 0;
    for(i=1;i<nargs;i++){
        args[i] = i;
        for(j=i-1;j>=0; j--){
            if(v[args[j]] <= v[args[j+1]])
                break;
            k = args[j];
            args[j] = args[j+1];
            args[j+1] = k;
        }
    }
    for(i=nargs;i<nv;i++){
        if(v[i] < v[args[nargs-1]]){
            args[nargs-1] = i;
            for(j=nargs-2; j>=0; j--){
                if(v[args[j]] <= v[args[j+1]])
                    break;
                k = args[j];
                args[j] = args[j+1];
                args[j+1] = k;
            }
        }
    }
}


/*  ARGMINLONG
 *
 *  Finds the argument of the smalles value in a long vector.
 *  
 *  Input:
 *      *v: vector with values to find its argument.
 *      nv: length of v.
 *
 *  Return: argument of the minimum value in v.
 */
int argMinLong(long *v, int nv){
    int i,argmin = 0;
    for(i=1; i<nv; i++)
        if(v[i]<v[argmin])
            argmin = i;
    return(argmin);
}
