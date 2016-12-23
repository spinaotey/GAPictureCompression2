#pragma once
#include "DNAPolygon.h"

typedef struct PicGen_s{
    unsigned char *r,*g,*b; //RGB of the picture
    int width, height;      //Width and height
    unsigned char bgrgb[3]; //background RGB
    int npoly;              //number of polygons
    struct Triangle_s *poly;//Vector of polygons
    char flag;              //flag to see if fitness was computed
    long fitness;           //fitness
}PicGen_t;

typedef struct Picprop_s{
    unsigned char *r,*g,*b; //RGB of picture
    int width,height;       //Width and height
    double sdCoords,sdColor;//Standard deviation of coordinates and color mutations
    double bd;              //bound differential
    unsigned char tb;       //transparency bound
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
