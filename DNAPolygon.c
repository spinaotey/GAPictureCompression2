#include "DNAPolygon.h"
#include "DNAPicture.h"
#include "myFunctions.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define POSBOUND(x,xmax) x < 0 ? 0 : (x >= xmax ? (xmax-1) : x)

/*  CROSSPOINT
 *
 *  Computes the intersection of one edge of the polygon at a certain "y"
 *  coordinate. 
 *  
 *  Input:
 *      x1,y1,x2,y2: coordinates of the vertices of the edge.
 *      y: intersection coordinate.
 *
 *  Return: floating point intersection coordinate.
 */
float crosspoint(int x1, int y1, int x2, int y2, int y){
    float m,n;
    m = (float)(x1-x2)/(float)(y1-y2);
    n = (float)x1-(float)y1*m;
    return((float)y*m+n);   
}

/* GETCROSSPOINTS
 *
 *  Computes all the crosspoints for a triangle for a y-axis value.
 *  
 *  Input:
 *      t: triangle.
 *      y: intersection coordinate.
 *      *cp: vector to save crosspoints.
 */
void getCrosspoints(Triangle_t t, int y, float *cp){
    int i,j;
    j = 0;
    for(i=0;i<3;i++){
        if(t.py[i]==y){
            cp[j] = t.px[i];
            j++;
        }else if((y>t.py[i] && y < t.py[(i+1)%3]) ||
                 (y<t.py[i] && y > t.py[(i+1)%3])){
            cp[j] = crosspoint(t.px[i],t.py[i],t.px[(i+1)%3],t.py[(i+1)%3],y);
            j++;
        }
    }
    /* If only one intersection, count point as two */
    if(j==1)
        cp[1] = cp[0];
}

/* COMPUTETRIANGLE
 *
 *  Computes the inner points of the triangle and saves them into
 *  the triangle variable. t->x/yfill has to be previously set to
 *  NULL or allocated or freed before because of free() function.
 *  
 *  Input:
 *      *t: triangle pointer to be compued and filled.
 */
void computeTriangle(Triangle_t *t){
    int ylim[2];
    int i,j;
    float cp[2];
    free(t->xFill);free(t->yFill);
    t->xFill = malloc(sizeof(int)*50); assert(t->xFill);
    t->yFill = malloc(sizeof(int)*50); assert(t->yFill);
    minMaxInt(t->py,3,ylim,ylim+1);
    t->nFill = 0;
    for(j=ylim[0];j<=ylim[1];j++){
        getCrosspoints(*t,j,cp);
        for(i=cp[0];i<=cp[1];i++){
            (t->nFill)++;
            if((t->nFill)%50 == 0){
                t->xFill = realloc(t->xFill,sizeof(int)*(t->nFill+50)); assert(t->xFill);
                t->yFill = realloc(t->yFill,sizeof(int)*(t->nFill+50)); assert(t->yFill);
            }
            t->xFill[t->nFill-1] = i;
            t->yFill[t->nFill-1] = j;
        }
    }
}

/* MUTATEPOINT
 *
 *  Computes the inner points of the triangle and saves them into
 *  the triangle variable. t->x/yfill has to be previously set to
 *  NULL or allocated or freed before because of free() function.
 *  
 *  Input:
 *      *t: triangle pointer whose random point has to be mutated.
 *      p: picture properties stucture.
 *      *seedp: seed to be pased for random number generation.
 */
void mutatePoint(Triangle_t *t, Picprop_t p, unsigned int *seedp){
    int i = randInt_r(seedp,3);
    double aux;
    aux = randNorm_r(seedp,0.,p.sdCoords);
    t->px[i] = (int) POSBOUND((double) (t->px[i]) + aux,p.width);
    aux = randNorm_r(seedp,0.,p.sdCoords);
    t->py[i] = (int) POSBOUND((double) (t->py[i]) + aux,p.height);
}

/* RANDOMPOINT
 *
 *  Computes random x and y coordinates inside the picture. There is a certain
 *  margin to get outside the picture given by p.bd on both sides, and the
 *  point is relocated at the margin.
 *  
 *  Input:
 *      *x: x-coordinate to generate randomly.
 *      *y: y-coordinate to generate randomly.
 *      p: picture properties stucture.
 *      *seedp: seed to be pased for random number generation.
 */
void randomPoint(int *x, int *y, Picprop_t p, unsigned int *seedp){
    *x = (int) (randUnif_r(seedp)*p.width*(1.+2.*p.bd)-p.width*p.bd);
    *x = POSBOUND(*x,p.width);
    *y = (int) (randUnif_r(seedp)*p.height*(1.+2.*p.bd)-p.height*p.bd);
    *y = POSBOUND(*y,p.height);
}
