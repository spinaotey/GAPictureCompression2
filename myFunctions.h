#define POW2(x) ((x)*(x))
#define POW2(x) ((x)*(x))
#define POW2(x) ((x)*(x))
#define PI  3.14159265358979323846264338327950288


/*  RANDUNIF_R
 *
 *  Returns random uniform number in [0,1) using a given seed.
 *
 *  Input:
 *      *seedp: pointer to seed which is modified.
 *
 *  Return: uniform number in [0,1).
 */
double randUnif_r(int *seedp);


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
double randStdNorm_r(int *seedp);


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
double randNorm_r(int *seedp, double mean, double sd);
