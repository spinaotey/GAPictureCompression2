#include "DNAPicture.h"
#include "DNAPolygon.h"
#include "myFunctions.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  MAKEPICTURE
 * 
 *  Takes as input a PicGen_t type and computes the RGB of its
 *  pixels using alpha composition and the triangles of the
 *  picture.
 *
 *  Input:
 *      *pic: Pointer to picture to be made.
 */
#define R(i,j) (pic->r[(j)*(pic->width)+i])
#define G(i,j) (pic->g[(j)*(pic->width)+i])
#define B(i,j) (pic->b[(j)*(pic->width)+i])
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
        if((pic->poly)[i].flag == 0)
            computeTriangle(&((pic->poly)[i]));
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
    pic->flag = 1;
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

/* COPYPICGEN
 *
 *  Copies a PicGen from input to output.
 *
 *  Input:
 *      *pin: PicGen to be copied.
 *      *pout: PicGen copying destination.
 */
void copyPicGen(PicGen_t *pin, PicGen_t *pout){
    int i;
    memcpy(pout->r, pin->r,sizeof(unsigned char)*(pin->width)*(pin->height));
    memcpy(pout->g, pin->g,sizeof(unsigned char)*(pin->width)*(pin->height));
    memcpy(pout->b, pin->b,sizeof(unsigned char)*(pin->width)*(pin->height));
    for(i=0; i<(pin->npoly);i++)
        copyTriangle2(&((pin->poly)[i]),&((pout->poly)[i]));
}

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
void mutatePicGen(PicGen_t *pic, Picprop_t p, Triangle_t *taux, unsigned int *seedp){
    int i,j,k,m,n;
    for(i=0; i <p.nMutate;i++){
        j = randInt_r(seedp,2);
        k = randInt_r(seedp,pic->npoly);
        if(j==0)
            mutateColor(&((pic->poly)[k]),p,seedp);
        else if(j==1)
            mutatePoint(&((pic->poly)[k]),p,seedp);
        else{
            m = randInt_r(seedp,pic->npoly);
            if(m>k){
                copyTriangle2(&pic->poly[k],taux);
                for(n=k+1;n<=m;n++)
                    copyTriangle2(&pic->poly[n],&pic->poly[n-1]);
                copyTriangle2(taux,&pic->poly[m]);
            }else if(m<k){
                copyTriangle2(&pic->poly[k],taux);
                for(n=k-1;n>=m;n--)
                    copyTriangle2(&pic->poly[n],&pic->poly[n+1]);
                copyTriangle2(taux,&pic->poly[m]);
            }
        }
    }
    pic->flag = 0;
}

/*  PRINTPICGEN
 *
 *  Creates image from PicGen_t and draws it into name file.
 *
 *  Input:
 *      pic: PicGen to be drawn.
 *      *name: String with output name and format.
 */ 
void printPicGen(PicGen_t pic, char *name){
    int i;
    FILE *tmp;
    char buffer[200];
    tmp = fopen("tmp.dat","w");
    for(i=0; i < (pic.width*pic.height);i++)
        fprintf(tmp,"%hhu,%hhu,%hhu\n",pic.r[i],pic.g[i],pic.b[i]);
    fclose(tmp);
    sprintf(buffer,"python toImage.py %d %d tmp.dat %s",pic.width,pic.height,name);
    system(buffer);
}

/*  INITIATEPICGEN
 *
 *  Allocates memory for PicGen and sets parameters.
 *
 *  Input:
 *      *pic: PicGen to be initiated.
 *      tarPic: Target picture data to be used to initiate.
 */ 
void initiatePicGen(PicGen_t *pic, Picprop_t tarPic){
    pic->r = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(pic->r);
    pic->g = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(pic->g);
    pic->b = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(pic->b);
    pic->width = tarPic.width;
    pic->height = tarPic.height;
    memcpy(pic->bgrgb,tarPic.bgrgb,sizeof(unsigned char)*3);
    pic->npoly = tarPic.npoly;
    pic->flag = 0;
    pic->poly = malloc(sizeof(Triangle_t)*tarPic.npoly); assert(pic->poly);
}

/*  FREEPICGEN
 *
 *  Frees memory from PicGen_t pointer. 
 *
 *  Input:
 *      *pic: PicGen to be freed.
 */ 
void freePicGen(PicGen_t *pic){
    int i;
    for(i=0;i<(pic->npoly);i++){
        free(pic->poly[i].xFill);
        free(pic->poly[i].yFill);
    }
    free(pic->poly);
    free(pic->r); free(pic->g); free(pic->b);
}
