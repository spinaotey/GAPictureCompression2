#include "DNAPicture.h"
#include "DNAPolygon.h"
#include "GAlib.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
    int maxIt;
    double p;
    int nPop,nChild,nPol;
    unsigned char bgrgb[3];
    Picprop_t tarPic;
    PicGen_t *population,*children,best;
    long *fitness,*childrenFitness, currentBestFitness;
    int i,j;
    unsigned int randomSeed = 0;
    
    /*READ INPUT*/
    fscanf(stdin,"maxIt:%d p:%lf\n",&maxIt,&p);
    fscanf(stdin,"nPop:%d nChild:%d nPol:%d nMutate:%d\n",&nPop,&nChild,&nPol,&tarPic.nMutate);
    fscanf(stdin,"background r:%hhu g:%hhu b:%hhu\n",&bgrgb[0],&bgrgb[1],&bgrgb[2]);
    fscanf(stdin,"sdCoords:%lf sdColor:%lf\n",&tarPic.sdCoords,&tarPic.sdColor);
    fscanf(stdin,"bd:%lf tb:%hhu\n",&tarPic.bd,&tarPic.tb);
    fscanf(stdin,"width:%d height:%d",&tarPic.width,&tarPic.height);

    /*ALLOCATE MEMORY/INITIATE POPULATION*/
    tarPic.r = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(tarPic.r);
    tarPic.g = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(tarPic.g);
    tarPic.b = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(tarPic.b);
    population = malloc(sizeof(PicGen_t)*nPop); assert(population);
    children = malloc(sizeof(PicGen_t)*nChild); assert(children);
    //Population
    for(i=0;i<nPop;i++){
        population[i].r = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(population[i].r);
        population[i].g = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(population[i].g);
        population[i].b = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(population[i].b);
        population[i].width = tarPic.width;
        population[i].height = tarPic.height;
        memcpy(population[i].bgrgb,bgrgb,sizeof(unsigned char)*3);
        population[i].npoly = nPol;
        population[i].flag = 0;
        population[i].poly = malloc(sizeof(Triangle_t)*nPol); assert(population[i].poly);
        for(j=0;j<nPol;j++)
            initTriangle(&(population[i].poly[j]),tarPic,&randomSeed,1);
    }
    //Children
    for(i=0;i<nChild;i++){
        children[i].r = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(children[i].r);
        children[i].g = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(children[i].g);
        children[i].b = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(children[i].b);
        children[i].width = tarPic.width;
        children[i].height = tarPic.height;
        memcpy(children[i].bgrgb,bgrgb,sizeof(unsigned char)*3);
        children[i].npoly = nPol;
        children[i].flag = 0;
        children[i].poly = malloc(sizeof(Triangle_t)*sizeof(nPol)); assert(children[i].poly);
        for(j=0;j<nPol;j++)
            children[i].poly[j].flag = 0;
    }
    return(0);
}
