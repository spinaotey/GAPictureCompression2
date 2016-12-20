#include "DNAPolygon.h"

void minMaxInt(int *v, int n, int *min, int *max){
    int i;
    *min = v[0];
    *max = v[0];
    for(i = 1; i<n; i++){
        if(v[i] < *min)
            *min = v[i];
        if(v[i] > *max)
            *max = v[i];
}

