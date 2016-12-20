typedef struct tri{
    int px[3],py[3];    //Coordinates of vertices
    int rgba[4];        //Color RGBA
    int nFill;          //Number of points inside polygon  
    int *xFill, *yFill; //Coordinates for filled points
}Triangle_t;

