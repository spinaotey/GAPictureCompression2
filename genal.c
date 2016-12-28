#include "DNAPicture.h"
#include "DNAPolygon.h"
#include "GAlib.h"
#include "myFunctions.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
    int maxIt;
    double probMut;
    int nPop,nChild,nPol;
    unsigned char bgrgb[3];
    Picprop_t tarPic;
    PicGen_t *population,*children,best;
    long *fitness,*childrenFitness, currentBestFitness;
    int i,j,argMin;
    unsigned int randomSeed = 0;
    char buffer1[200],buffer2[200];
    FILE *file;
    
    /*READ INPUT*/
    fscanf(stdin,"maxIt:%d p:%lf\n",&maxIt,&probMut);
    fscanf(stdin,"nPop:%d nChild:%d nPol:%d nMutate:%d\n",&nPop,&nChild,&tarPic.npoly,&tarPic.nMutate);
    fscanf(stdin,"background r:%hhu g:%hhu b:%hhu\n",&(tarPic.bgrgb[0]),&(tarPic.bgrgb[1]),&(tarPic.bgrgb[2]));
    fscanf(stdin,"sdCoords:%lf sdColor:%lf\n",&tarPic.sdCoords,&tarPic.sdColor);
    fscanf(stdin,"bd:%lf tb:%hhu\n",&tarPic.bd,&tarPic.tb);
    fscanf(stdin,"imageName:%s",buffer1);
    sprintf(buffer2,"python imgToCSV.py %s",buffer1);
    system(buffer2);
    file = fopen("target.csv","r");
    fscanf(file,"%d,%d",&tarPic.width,&tarPic.height);
    tarPic.r = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(tarPic.r);
    tarPic.g = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(tarPic.g);
    tarPic.b = malloc(sizeof(unsigned char)*tarPic.height*tarPic.width); assert(tarPic.b);
    for(i=0; i<(tarPic.width*tarPic.height);i++)
        fscanf(file,"%hhu,%hhu,%hhu",&tarPic.r[i],&tarPic.g[i],&tarPic.b[i]);
    fclose(file);

    /*ALLOCATE MEMORY/INITIATE POPULATION*/
    population = malloc(sizeof(PicGen_t)*nPop); assert(population);
    children = malloc(sizeof(PicGen_t)*nChild); assert(children);
    fitness = malloc(sizeof(long)*nPop); assert(fitness);
    childrenFitness = malloc(sizeof(long)*nChild); assert(childrenFitness);
    //Population
    for(i=0;i<nPop;i++){
        initiatePicGen(&population[i],tarPic);
        for(j=0;j<tarPic.npoly;j++)
            initTriangle(&(population[i].poly[j]),tarPic,&randomSeed,1);
        makePicture(&(population[i]));
        fitness[i] = getFitness(population[i],tarPic);
    }
    argMin = argMinLong(fitness,nPop);
    printPicGen(population[argMin],"initialbest.png");
    
    //Children
    for(i=0;i<nChild;i++){
        initiatePicGen(&children[i],tarPic);
        for(j=0;j<tarPic.npoly;j++){
            children[i].poly[j].flag = 0;
            children[i].poly[j].xFill = NULL; children[i].poly[j].yFill= NULL;
        }
    }


    /*FREE MEMORY*/
    for(i=0;i<nPop;i++)
        freePicGen(&population[i]);
    free(population);
    for(i=0;i<nChild;i++)
        freePicGen(&children[i]);
    free(children);
    free(tarPic.r); free(tarPic.g); free(tarPic.b); 
    free(fitness); free(childrenFitness);
    return(0);
}
