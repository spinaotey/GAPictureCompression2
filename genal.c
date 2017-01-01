#include "DNAPicture.h"
#include "DNAPolygon.h"
#include "GAlib.h"
#include "myFunctions.h"
#include <assert.h>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int main(void){
    int maxIt;
    double probMut;
    int nPop,nChild,nTour,nFittest;
    Picprop_t tarPic;
    PicGen_t *population,*children,bestPicGen;
    Triangle_t *taux;
    long *fitness,*childrenFitness,bestFitness,prevFitness;
    int i,j,k,id;
    int argMin, *argBests;
    int parent1arg, parent2arg,crossPoint;
    unsigned int randomSeed,*parallelSeed;
    struct timeval tval_before, tval_after, tval_result;
    char buffer1[200],buffer2[200],buffer3[100];
    FILE *file;
    
    /*READ INPUT*/
    fscanf(stdin,"maxIt:%d p:%lf\n",&maxIt,&probMut);
    fscanf(stdin,"nPop:%d nChild:%d nPol:%d nMutate:%d nTour:%d\n",&nPop,&nChild,&tarPic.npoly,&tarPic.nMutate,&nTour);
    fscanf(stdin,"background r:%hhu g:%hhu b:%hhu\n",&(tarPic.bgrgb[0]),&(tarPic.bgrgb[1]),&(tarPic.bgrgb[2]));
    fscanf(stdin,"sdCoords:%lf sdColor:%lf\n",&tarPic.sdCoords,&tarPic.sdColor);
    fscanf(stdin,"bd:%lf tb:%hhu\n",&tarPic.bd,&tarPic.tb);
    fscanf(stdin,"picSufix:%s\n",buffer3);
    fscanf(stdin,"randSeed:%u imageName:%s",&randomSeed,buffer1);
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

    /*ALLOCATE MEMORY/INITIATE POPULATION*/
    nFittest = nPop-nChild;
    population = malloc(sizeof(PicGen_t)*nPop); assert(population);
    children = malloc(sizeof(PicGen_t)*nChild); assert(children);
    fitness = malloc(sizeof(long)*nPop); assert(fitness);
    childrenFitness = malloc(sizeof(long)*nChild); assert(childrenFitness);
    argBests = malloc(sizeof(int)*(nFittest)); assert(argBests);
    //Population
    for(i=0;i<nPop;i++){
        initiatePicGen(&population[i],tarPic);
        for(j=0;j<tarPic.npoly;j++)
            initTriangle(&(population[i].poly[j]),tarPic,&randomSeed,0);
        makePicture(&(population[i]));
        fitness[i] = getFitness(population[i],tarPic);
    }
    //Children
    for(i=0;i<nChild;i++){
        initiatePicGen(&children[i],tarPic);
        for(j=0;j<tarPic.npoly;j++)
            initTriangle(&children[i].poly[j],tarPic,&randomSeed,0);
    }
    //Best
    initiatePicGen(&bestPicGen,tarPic);
    for(j=0;j<tarPic.npoly;j++)
        initTriangle(&bestPicGen.poly[j],tarPic,&randomSeed,0);
    argMin = argMinLong(fitness,nPop);
    bestFitness = fitness[argMin];
    prevFitness = bestFitness;
    //Parallel
    parallelSeed = malloc(sizeof(unsigned int)*4);
    taux = malloc(sizeof(Triangle_t)*4);
    for(i=0; i<4;i++){
        parallelSeed[i] = i+randomSeed;
        initTriangle(&taux[i],tarPic,&parallelSeed[i],0);
    }

    /*GENETIC ALGORITHM*/
    sprintf(buffer1,"%s.dat",buffer3);
    file = fopen(buffer1,"w");
    //Main Loop
    for(i=1;i<=maxIt;i++){
        gettimeofday(&tval_before,NULL);
        #pragma omp parallel for private(j,parent1arg,parent2arg,id,crossPoint) \
                                 shared(nChild,fitness,nPop,nTour,parallelSeed,tarPic,population,children,probMut,taux,childrenFitness)
        for(j=0;j<nChild/2;j++){
            id = omp_get_thread_num();
            //Select parents at random via Tournament
            parent1arg = tournament(fitness,nPop,nTour,&parallelSeed[id]);
            parent2arg = tournament(fitness,nPop,nTour,&parallelSeed[id]);
            //Get random crosspoint for one-point-crossover
            crossPoint = randInt_r(&parallelSeed[id],tarPic.npoly-2)+1;
            crossover(&population[parent1arg],&population[parent2arg],
                      &children[2*j],&children[2*j+1],crossPoint);
            //Mutate randomly both children
            if(randUnif_r(&parallelSeed[id]) < probMut)
                mutatePicGen(&children[2*j],tarPic,&taux[id],&parallelSeed[id]);
            if(randUnif_r(&parallelSeed[id]) < probMut)
                mutatePicGen(&children[2*j+1],tarPic,&taux[id],&parallelSeed[id]);
            //Compute their fitness and store it
            makePicture(&children[2*j]);
            makePicture(&children[2*j+1]);
            childrenFitness[2*j] = getFitness(children[2*j],tarPic);
            childrenFitness[2*j+1] = getFitness(children[2*j+1],tarPic);
        }
        //Get fittest individuals and substitute the others with children
        argsMinLong(fitness,nPop,argBests,nFittest);
        for(j=0,k=0;j<nPop;j++){
            if(!isInInt(argBests,nFittest,j)){
                copyPicGen(&children[k],&population[j]);
                fitness[j] = childrenFitness[k];
                k++;
            }
        }
        //Get fittest individual of this generation and substitute if necessary
        argMin = argMinLong(fitness,nPop);
        if(fitness[argMin] < bestFitness){
            bestFitness = fitness[argMin];
            copyPicGen(&population[argMin],&bestPicGen);
        }
        //Print time and current fitness
        gettimeofday(&tval_after,NULL);
        timersub(&tval_after,&tval_before,&tval_result);
        fprintf(file,"%7d %2ld.%06ld %14ld\n",i,
                (long int)tval_result.tv_sec,(long int)tval_result.tv_usec,
                fitness[argMin]);
        //If 1% improved, print picture
        if(prevFitness*0.99 > fitness[argMin]){
            prevFitness = fitness[argMin];
            sprintf(buffer1,"%s%08d.png",buffer3,i);
            printPicGen(population[argMin],buffer1);
        }
    }
    fclose(file);

    /*FREE MEMORY*/
    for(i=0;i<nPop;i++)
        freePicGen(&population[i]);
    free(population);
    for(i=0;i<nChild;i++)
        freePicGen(&children[i]);
    free(children);
    freePicGen(&bestPicGen);
    free(tarPic.r); free(tarPic.g); free(tarPic.b); 
    free(fitness); free(childrenFitness);
    return(0);
}
