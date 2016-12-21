#pragma once
typedef struct pic{
    int *r,*g,*b;
    int width,height;
    double sdCoords,sdColor;
    double bd;
    unsigned char tb;
}Picprop_t;
