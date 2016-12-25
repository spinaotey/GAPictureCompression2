#include "GAlib.h"
#include "DNAPicture.h"
#include "DNAPolygon.h"
#include "myFunctions.h"

/*  CROSSOVER
 *
 *  Performs a one-point crossover on the polygons of both parents to produce
 *  two children. The point to do the crossover is passed as argument j.
 *
 *  Input:
 *      *p1: pointer to first parent.
 *      *p2: pointer to second parent.
 *      *c1: pointer to first child.
 *      *c2: pointer to second child.
 */
void crossover(PicGen_t *p1,PicGen_t *p2,PicGen_t *c1,PicGen_t *c2, int j){
    int i;
    c1->flag = 0; c2->flag = 0;
    for(i=0; i<j; i++){
        copyTriangle2(&((p1->poly)[i]),&((c1->poly)[i]));
        copyTriangle2(&((p2->poly)[i]),&((c2->poly)[i]));
    }
    for(i=j; i<(p1->npoly); i++){
        copyTriangle2(&((p1->poly)[i]),&((c2->poly)[i]));
        copyTriangle2(&((p2->poly)[i]),&((c1->poly)[i]));
    }
}


/*  TOURNAMENT
 *
 *  Tournament of nTour participants with repetition to select argument of
 *  best fitness (smallest).
 *
 *  Input:
 *      *v: vector of fitness.
 *      *nv: length of vector.
 *      nTour: number of tournament participants.
 *      *seedp: random number generator seed.
 *
 *  Return: argument of winner of the tournament.
 */
int tournament(long *v, int nv, int nTour,unsigned int *seedp){
    int min,i,j;
    min = randInt_r(seedp,nv);
    for(i=1;i<nTour;i++){
        j = randInt_r(seedp,nv);
        if(v[j]< v[min])
            min = j;
    }
    return(min);
}
