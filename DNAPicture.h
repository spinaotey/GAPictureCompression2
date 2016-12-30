#pragma once
#include "DNAPolygon.h"

typedef struct Triangle_s Triangle_t;

typedef struct PicGen_s{
    unsigned char *r,*g,*b; //RGB of the picture
    int width, height;      //Width and height
    unsigned char bgrgb[3]; //background RGB
    int npoly;              //number of polygons
    Triangle_t *poly;//Vector of polygons
    char flag;              //flag to see if fitness was computed
}PicGen_t;

typedef struct Picprop_s{
    unsigned char *r,*g,*b; //RGB of picture
    int width,height;       //Width and height
    double sdCoords,sdColor;//Standard deviation of coordinates and color mutations
    double bd;              //bound differential
    unsigned char tb;       //transparency bound
    int npoly;              //number of polygons
    unsigned char bgrgb[3]; //background RGB
    int nMutate;            //number of polygons to mutate each time
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

/*  GETFINTESS
 * 
 *  Computes fitness as the square difference in RGB channesl
 *  between target picture and PicGen.
 *
 *  Input:
 *      pic: picture fitness to be computed.
 *      tar: target picture struture.
 *
 *  Return: Fitness value.
 */
long getFitness(PicGen_t pic, Picprop_t tar);

/* COPYPICGEN
 *
 *  Copies a PicGen from input to output.
 *
 *  Input:
 *      *pin: PicGen to be copied.
 *      *pout: PicGen copying destination.
 */
void copyPicGen(PicGen_t *pin, PicGen_t *pout);

/*  MUTATEPICGEN
 *
 *  Mutates PicGen, changing nMutate polygons, either by mutating color,
 *  vertex position or position of the polygon within the picture.
 *
 *  Input:
 *      *pic: PicGen to be mutated.
 *      p: PicProp with the necessary conditions for the mutation.
 *      *seedp: seed for random number generation.
 */ 
void mutatePicGen(PicGen_t *pic, Picprop_t p, Triangle_t *taux, unsigned int *seedp);

/*  PRINTPICGEN
 *
 *  Creates image from PicGen_t and draws it into name file.
 *
 *  Input:
 *      pic: PicGen to be drawn.
 *      *name: String with output name and format.
 */ 
void printPicGen(PicGen_t pic, char *name);

/*  INITIATEPICGEN
 *
 *  Allocates memory for PicGen and sets parameters.
 *
 *  Input:
 *      *pic: PicGen to be initiated.
 *      tarPic: Target picture data to be used to initiate.
 */ 
void initiatePicGen(PicGen_t *pic, Picprop_t tarPic);

/*  FREEPICGEN
 *
 *  Frees memory from PicGen_t pointer. 
 *
 *  Input:
 *      *pic: PicGen to be freed.
 */ 
void freePicGen(PicGen_t *pic);
