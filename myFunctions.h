#pragma once
#define POW2(x) (x == 0 ? 0 :(x)*(x))
#define POW4(x) (x == 0 ? 0 :(x)*(x)*(x)*(x))
#define PI  3.14159265358979323846264338327950288

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
double randUnif_r(unsigned int *seedp);


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
double randStdNorm_r(unsigned int *seedp);


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
double randNorm_r(unsigned int *seedp, double mean, double sd);

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
int randInt_r(unsigned int *seedp, int n);

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
void minMaxInt(int *v, int n, int *min, int *max);

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
void argsMinLong(long *v, int nv, int *args, int nargs);

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
int argMinLong(long *v, int nv);

/*  ISININT
 *
 *  Checks if a target value is in a vector for integers.
 *
 *  Input:
 *      *v: vector to search.
 *      nv: length of vector.
 *      tar: target number.
 *
 *  Return: 1 if it is in vector, 0 if not.
 */
int isInInt(int *v, int nv, int tar);

/*  BOUNDEDINT
 *
 *  Checks if x is outside of bounds. If so, it returns boundaries.
 *
 *  Input:
 *      x: value to check.
 *      xmin: minimum value.
 *      xmax: maximum value.
 *
 *  Return: x if it is inside boundaries, else boundaries.
 */
int boundedInt(int x, int xmin, int xmax);

/*  BOUNDEDUCHAR
 *
 *  Checks if x is outside of bounds. If so, it returns boundaries.
 *
 *  Input:
 *      x: value to check.
 *      xmin: minimum value.
 *      xmax: maximum value.
 *
 *  Return: x if it is inside boundaries, else boundaries.
 */
unsigned char boundedUChar(unsigned char x, unsigned char xmin, unsigned char xmax);

/*  BOUNDEDDOUBLE
 *
 *  Checks if x is outside of bounds. If so, it returns boundaries.
 *
 *  Input:
 *      x: value to check.
 *      xmin: minimum value.
 *      xmax: maximum value.
 *
 *  Return: x if it is inside boundaries, else boundaries.
 */
double boundedDouble(double x, double xmin, double xmax);
