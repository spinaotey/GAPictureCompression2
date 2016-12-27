#pragma once
#include "DNAPicture.h"

typedef struct Triangle_s{
    int px[3],py[3];    //Coordinates of vertices
    unsigned char rgba[4];        //Color RGBA
    int nFill;          //Number of points inside polygon  
    int *xFill, *yFill; //Coordinates for filled points
    char flag; // flag wheter inner points are computed or not
}Triangle_t;

typedef struct Picprop_s Picprop_t;

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
float crosspoint(int x1, int y1, int x2, int y2, int y);


/* GETCROSSPOINTS
 *
 *  Computes all the crosspoints for a triangle for a y-axis value.
 *  
 *  Input:
 *      t: triangle.
 *      y: intersection coordinate.
 *      *cp: vector to save crosspoints.
 */
void getCrosspoints(Triangle_t t, int y, float *cp);


/* COMPUTETRIANGLE
 *
 *  Computes the inner points of the triangle and saves them into
 *  the triangle variable. t->x/yfill has to be previously set to
 *  NULL or allocated or freed before because of free() function.
 *  
 *  Input:
 *      *t: triangle pointer to be compued and filled.
 */
void computeTriangle(Triangle_t *t);

/* MUTATE POINT
 *
 *  Mutates a random point of the triangle using a gaussian distribution
 *  for the displacement.
 *  
 *  Input:
 *      *t: triangle pointer whose random point has to be mutated.
 *      p: picture properties stucture.
 *      *seedp: seed to be passed for random number generation.
 */
void mutatePoint(Triangle_t *t, Picprop_t p, unsigned int *seedp);

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
void randomPoint(int *x, int *y, Picprop_t p, unsigned int *seedp);


/* MUTATEPOINT2
 *
 *  Mutates a random point of the triangle, placing it at random.
 *  
 *  Input:
 *      *t: triangle pointer whose random point has to be mutated.
 *      p: picture properties stucture.
 *      *seedp: seed to be passed for random number generation.
 */
void mutatePoint2(Triangle_t *t, Picprop_t p, unsigned int *seedp);


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
void mutateColor(Triangle_t *t, Picprop_t p, unsigned int *seedp);


/* MUTATECOLOR2
 *
 *  Mutates the color of the triangle, placing it at random.
 *  
 *  Input:
 *      *t: triangle pointer whose color has to be mutated.
 *      p: picture properties stucture.
 *      *seedp: seed to be passed for random number generation.
 */
void mutateColor2(Triangle_t *t, Picprop_t p, unsigned int *seedp);

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
void initTriangle(Triangle_t *t,Picprop_t p,unsigned int *seedp, char flag);

/* COPYTRIANGLE
 *
 *  Copies a triangle into a new structure, allocating memory if necessary.
 *
 *  Input:
 *      tin: triangle to be copied.
 *
 *  Return: copy of triangle.
 */
Triangle_t copyTriangle(Triangle_t tin);

/* COPYTRIANGLE2
 *
 *  Copies a triangles from input to output.
 *
 *  Input:
 *      *tin: triangle to be copied.
 *      *tout: triangle copying destination.
 */
void copyTriangle2(Triangle_t *tin, Triangle_t *tout);
