#include "DNAPicture.h"
#include "DNAPolygon.h"
#include "myFunctions.h"


/*  MAKEPICTURE
 * 
 *  Takes as input a PicGen_t type and computes the RGB of its
 *  pixels using alpha composition and the triangles of the
 *  picture.
 *
 *  Input:
 *      *pic: Pointer to picture to be made.
 */
#define R(i,j) (pic->r[(i)*(pic->width)+j])
#define G(i,j) (pic->g[(i)*(pic->width)+j])
#define B(i,j) (pic->b[(i)*(pic->width)+j])
void makePicture(PicGen_t *pic){
    int i,j,x,y;
    unsigned char *rgba;
    float alpha,beta;
    // Get background
    for(i=0;i<(pic->width*pic->height);i++){
        pic->r[i] = pic->bgrgb[0];
        pic->g[i] = pic->bgrgb[1];
        pic->b[i] = pic->bgrgb[2];
    }
    for(i=0;i<(pic->npoly);i++){
        rgba = (pic->poly[i]).rgba;
        alpha = (float) rgba[3]/255.f;
        beta = 1.f-alpha;
        for(j=0;j<((pic->poly[i]).nFill);j++){
            x = (pic->poly[i]).xFill[j];
            y = (pic->poly[i]).yFill[j];
            R(x,y) = (unsigned char) (R(x,y)*beta+rgba[0]*alpha);
            G(x,y) = (unsigned char) (G(x,y)*beta+rgba[1]*alpha);
            B(x,y) = (unsigned char) (B(x,y)*beta+rgba[2]*alpha);
        }
    }
}
#undef R
#undef G
#undef B

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
long getFitness(PicGen_t pic, Picprop_t tar){
    int i;
    long fitness,d;
    fitness = 0;
    for(i=0;i<(pic.width*pic.height);i++){
        d = tar.r[i] - pic.r[i];
        fitness += POW2(d);
        d = tar.g[i] - pic.g[i];
        fitness += POW2(d);
        d = tar.b[i] - pic.b[i];
        fitness += POW2(d);
    }
    return(fitness);
}
