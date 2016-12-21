#pragma once


typedef struct{
    int *r,*g,*b;
    int width, height;
    unsigned char bgrgb[3];
    int npoly;
    Triangle_t *poly;
    char flag;
    long fitness;
}PicGen_t;

typedef struct{
    int *r,*g,*b;
    int width,height;
    double sdCoords,sdColor;
    double bd;
    unsigned char tb;
}Picprop_t;
