#pragma once
#include "DNAPicture.h"
#include "DNAPolygon.h"

typedef struct PicGen_s PicGen_t;

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
void crossover(PicGen_t *p1,PicGen_t *p2,PicGen_t *c1,PicGen_t *c2, int j);

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
int tournament(long *v, int nv, int nTour,unsigned int *seedp);
