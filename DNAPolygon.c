#include "DNAPolygon.h"

/*  MINMAXINT
 *
 *  Computes the minimum and maximum of an integer vector.
 *  
 *  Input:
 *      *v: pointer of the vector.
 *      n: length of the vector.
 *      *min: pointer to save minimum.
 *      *max: pointer to save maximum.
 */
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
}



/*  CROSSPOINT
 *
 *  Computes the intersection of one edge of the polygon at a certain "y"
 *  coordinate. 
 *  
 *  Input:
 *      x1,y1,x2,y2: coordinates of the vertices of the edge.
 *      y: intersection coordinate.
 *
 *  Return: floating point intersection coordinate.
 */
float crosspoint(int x1, int y1, int x2, int y2, int y){
    float m,n;
    m = (float)(x1-x2)/(float)(y1-y2);
    n = (float)x1-(float)y1*m;
    return((float)y*m+n);   
}

/* GETCROSSPOINTS
 *
 *  Computes all the crosspoints for a triangle for a y-axis value.
 *  
 *  Input:
 *      t: triangle.
 *      y: intersection coordinate.
 *      *cp: vector to save crosspoints.
 */
void getCrosspoints(Triangle_t t, int y, float *cp){
    int i,j;
    j = 0;
    for(i=0;i<3;i++){
        if(t.py[i]==y){
            cp[j] = t.px[i];
            j++;
        }else if((y>t.py[i] && y < t.py[(i+1)%3]) ||
                 (y<t.py[i] && y > t.py[(i+1)%3])){
            cp[j] = crosspoint(t.px[i],t.py[i],t.px[(i+1)%3],t.py[(i+1)%3],y);
            j++;
        }
    }
    /* If only one intersection, count point as two */
    if(j==1)
        cp[1] = cp[0];
}
