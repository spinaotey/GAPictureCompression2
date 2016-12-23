#pragma once
#include "DNAPolygon.h"

typedef struct PicGen_s{
    unsigned char *r,*g,*b;
    int width, height;
    unsigned char bgrgb[3];
    int npoly;
    struct Triangle_s *poly;
    char flag;
    long fitness;
}PicGen_t;

typedef struct Picprop_s{
    unsigned char *r,*g,*b;
    int width,height;
    double sdCoords,sdColor;
    double bd;
    unsigned char tb;
}Picprop_t;


/*  MAKEPICTURE
 * 
 *  Takes as input a PicGen_t type and computes the RGB of its
 *  pixels using alpha composition and the triangles of the
 *  picture.
 *
 *  Input:
 *      *pic: Pointer to picture to be made.
 */
void makePicture(PicGen_t *pic);
