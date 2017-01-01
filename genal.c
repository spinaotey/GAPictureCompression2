#include "DNAPicture.h"
#include "DNAPolygon.h"
#include "GAlib.h"
#include "myFunctions.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int main(void){
    int maxIt;
    Picprop_t tarPic;
    PicGen_t parent,child; 
    Triangle_t *taux;
    long fitness,childFitness,prevFitness;
    int i,j,k;
    unsigned int randomSeed ;
    struct timeval tval_before, tval_after, tval_result;
    char buffer1[200],buffer2[200],buffer3[100];
    FILE *file;
    
    /*READ INPUT*/
    fscanf(stdin,"maxIt:%d\n",&maxIt);
    fscanf(stdin,"nPol:%d\n",&tarPic.npoly);
    fscanf(stdin,"background r:%hhu g:%hhu b:%hhu\n",&(tarPic.bgrgb[0]),&(tarPic.bgrgb[1]),&(tarPic.bgrgb[2]));
    fscanf(stdin,"sdCoords:%lf sdColor:%lf\n",&tarPic.sdCoords,&tarPic.sdColor);
    fscanf(stdin,"bd:%lf tb:%hhu\n",&tarPic.bd,&tarPic.tb);
    fscanf(stdin,"picSufix:%s\n",buffer3);
    fscanf(stdin,"randSeed:%u imageName:%s",&randomSeed,buffer1);
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
    tarPic.nMutate=1;

    /*ALLOCATE MEMORY/INITIATE POPULATION*/
    taux = malloc(sizeof(Triangle_t)); assert(taux);
    //Population
    initiatePicGen(&parent,tarPic);
    for(j=0;j<tarPic.npoly;j++)
        initTriangle(&parent.poly[j],tarPic,&randomSeed,0);
    makePicture(&parent);
    fitness = getFitness(parent,tarPic);
    prevFitness = fitness;
    //Children
    initiatePicGen(&child,tarPic);
    for(j=0;j<tarPic.npoly;j++)
        initTriangle(&child.poly[j],tarPic,&randomSeed,0);
    
    initTriangle(taux,tarPic,&randomSeed,0);
    
    /*GENETIC ALGORITHM*/
    sprintf(buffer1,"%s.dat",buffer3);
    file = fopen(buffer1,"w");
    for(i=1;i<=maxIt;i++){
        gettimeofday(&tval_before,NULL);
        //Copy and mutate parent
        copyPicGen(&parent,&child);
        mutatePicGen(&child,tarPic,taux,&randomSeed);
        //Compute fitness of child
        makePicture(&child);
        childFitness = getFitness(child,tarPic);
        //If there is improvement, copy child to parent
        if(childFitness < fitness){
            fitness = childFitness;
            copyPicGen(&child,&parent);
        }
        //If Fitness has improved 1%, print result
        if(prevFitness*0.99 > fitness){
            prevFitness = fitness;
            sprintf(buffer1,"%s%08d.png",buffer3,i);
            printPicGen(parent,buffer1);
        }
        gettimeofday(&tval_after,NULL);
        timersub(&tval_after,&tval_before,&tval_result);
        fprintf(file,"%7d %2ld.%06ld %14ld\n",i,
                (long int)tval_result.tv_sec,(long int)tval_result.tv_usec,
                fitness);
    }
    fclose(file);

    /*FREE MEMORY*/
    freePicGen(&parent);
    freePicGen(&child);
    free(taux->xFill);
    free(taux->yFill);
    free(taux);
    free(tarPic.r); free(tarPic.g); free(tarPic.b); 
    return(0);
}
