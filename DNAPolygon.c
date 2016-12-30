#include "DNAPolygon.h"
#include "DNAPicture.h"
#include "myFunctions.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int cpInt[2];
    float cp[2];
    minMaxInt(t->py,3,ylim,ylim+1);
    t->nFill = 0;
    for(j=ylim[0];j<=ylim[1];j++){
        getCrosspoints(*t,j,cp);
        cpInt[0] = (int) cp[0];
        cpInt[1] = (int) cp[1];
        for(i=cpInt[0];i<=cpInt[1];i++){
            (t->nFill)++;
            t->xFill[t->nFill-1] = i;
            t->yFill[t->nFill-1] = j;
        }
    }
    t->flag = 1;
}

/* MUTATEPOINT
 *
 *  Mutates a random point of the triangle using a gaussian distribution
 *  for the displacement.
 *  
 *  Input:
 *      *t: triangle pointer whose random point has to be mutated.
 *      p: picture properties stucture.
 *      *seedp: seed to be passed for random number generation.
 */
void mutatePoint(Triangle_t *t, Picprop_t p, unsigned int *seedp){
    int i = randInt_r(seedp,3);
    double aux;
    aux = randNorm_r(seedp,0.,p.sdCoords)+t->px[i];
    t->px[i] = boundedInt((int) aux,0,p.width-1);
    aux = randNorm_r(seedp,0.,p.sdCoords)+t->py[i];
    t->py[i] = boundedInt((int) aux,0,p.height-1);
    t->flag = 0;
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
 *      *seedp: seed to be passed for random number generation.
 */
void randomPoint(int *x, int *y, Picprop_t p, unsigned int *seedp){
    *x = (int) (randUnif_r(seedp)*p.width*(1.+2.*p.bd)-p.width*p.bd);
    *x = boundedInt(*x,0,p.width-1);
    *y = (int) (randUnif_r(seedp)*p.height*(1.+2.*p.bd)-p.height*p.bd);
    *y = boundedInt(*y,0,p.height-1);
}

/* MUTATEPOINT2
 *
 *  Mutates a random point of the triangle, placing it at random.
 *  
 *  Input:
 *      *t: triangle pointer whose random point has to be mutated.
 *      p: picture properties stucture.
 *      *seedp: seed to be passed for random number generation.
 */
void mutatePoint2(Triangle_t *t, Picprop_t p, unsigned int *seedp){
    int i = randInt_r(seedp,3);
    randomPoint(&(t->px[i]),&(t->py[i]),p,seedp);
    t->flag = 0;
}


/* MUTATECOLOR
 *
 *  Mutates rgba colors of the triangle using a gaussian distribution
 *  for the displacement.
 *  
 *  Input:
 *      *t: triangle pointer whose color has to be mutated.
 *      p: picture properties stucture.
 *      *seedp: seed to be passed for random number generation.
 */
void mutateColor(Triangle_t *t, Picprop_t p, unsigned int *seedp){
    double aux;
    int i;
    for(i=0; i<3; i++){
        aux = randNorm_r(seedp,0.,p.sdColor)+t->rgba[i];
        aux = boundedDouble(aux,0.,255.);
        t->rgba[i] = (unsigned char) aux;
    }
    aux = randNorm_r(seedp,0.,p.sdColor)+t->rgba[3];
    aux = boundedDouble(aux,0.,(double)p.tb);
    t->rgba[3] = (unsigned char) aux;
}

/* MUTATECOLOR2
 *
 *  Mutates the color of the triangle, placing it at random.
 *  
 *  Input:
 *      *t: triangle pointer whose color has to be mutated.
 *      p: picture properties stucture.
 *      *seedp: seed to be passed for random number generation.
 */
void mutateColor2(Triangle_t *t, Picprop_t p, unsigned int *seedp){
    int i;
    for(i=0; i<3; i++)
        t->rgba[i] = (unsigned char) randInt_r(seedp,256);
    t->rgba[3] = (unsigned char) randInt_r(seedp,p.tb);
}


/*  INITTRIANGLE
 *
 *  Initiates triangle structure's  coordinates
 *  and colors. Flag indicates whether colors are chosen at
 *  random or all to black, with zero transparency.
 *
 *  Input:
 *      *t: pointer to triangle to be initiated.
 *      p: picture properties.
 *      *seedp: seed to be passed for random number generation.
 *      flag: 0 all are set to black, else random color.
 */
void initTriangle(Triangle_t *t,Picprop_t p,unsigned int *seedp, char flag){
    int i;
    for(i=0;i<3;i++)
        randomPoint(&((t->px)[i]),&((t->py)[i]),p,seedp);
    if(flag == 0)
        for(i=0;i<4;i++)
            t->rgba[i] = 0;
    else
        mutateColor2(t,p,seedp);
    t->nFill = 0;
    t->xFill = malloc(sizeof(int)*p.width*p.height); assert(t->xFill);
    t->yFill = malloc(sizeof(int)*p.width*p.height); assert(t->yFill);
    t->flag = 0;
}

/* COPYTRIANGLE
 *
 *  Copies a triangle into a new structure, allocating memory if necessary.
 *
 *  Input:
 *      tin: triangle to be copied.
 *
 *  Return: copy of triangle.
 */
Triangle_t copyTriangle(Triangle_t tin){
    Triangle_t tout;
    tout = tin;
    if(tin.flag == 1 && tin.nFill > 0){
        tout.xFill = malloc(tin.nFill*sizeof(int)); assert(tout.xFill);
        tout.yFill = malloc(tin.nFill*sizeof(int)); assert(tout.yFill);
        memcpy(tout.xFill,tin.xFill,sizeof(int)*tin.nFill);
        memcpy(tout.yFill,tin.yFill,sizeof(int)*tin.nFill);
    }else{
        tout.nFill = 0;
        tout.xFill = NULL; tout.yFill = NULL;
    }
    return(tout);
}

/* COPYTRIANGLE2
 *
 *  Copies a triangles from input to output.
 *
 *  Input:
 *      *tin: triangle to be copied.
 *      *tout: triangle copying destination.
 */
void copyTriangle2(Triangle_t *tin, Triangle_t *tout){
    /*if(tout->flag == 1 && tout->nFill > 0){
        free(tout->xFill); free(tout->yFill);
    }
    *tout = *tin;
    tout->xFill = malloc(tin->nFill*sizeof(int)); assert(tout->xFill);
    tout->yFill = malloc(tin->nFill*sizeof(int)); assert(tout->yFill);
    memcpy(tout->xFill,tin->xFill,sizeof(int)*(tin->nFill));
    memcpy(tout->yFill,tin->yFill,sizeof(int)*(tin->nFill));*/
    /*if(tout->xFill == NULL)
        tout->xFill = malloc(sizeof(int)*tin->nFill);
    else
        tout->xFill = realloc(tout->xFill,sizeof(int)*tin->nFill);
    if(tout->yFill == NULL)
        tout->yFill = malloc(sizeof(int)*tin->nFill);
    else
        tout->yFill = realloc(tout->yFill,sizeof(int)*tin->nFill);*/
    memcpy(tout->xFill,tin->xFill,sizeof(int)*tin->nFill);
    memcpy(tout->yFill,tin->yFill,sizeof(int)*tin->nFill);
    memcpy(tout->px,tin->px,sizeof(int)*3);
    memcpy(tout->py,tin->py,sizeof(int)*3);
    memcpy(tout->rgba,tin->rgba,sizeof(unsigned char)*4);
    tout->nFill = tin->nFill;
    tout->flag = tin->flag;
}
