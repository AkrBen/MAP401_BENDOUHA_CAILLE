#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "geom2d.h"
#include "image.h"
#include "exemple_sequence_point.c"

typedef enum {Nord , Est , Sud , Ouest } Orientation;

typedef struct{
    Orientation orientation;
    Point position;
} Robot;

Robot nouveauRobot();
void avancer(Robot r);
void nouvelle_orientation(Robot r);
Contour calcul_ecriture_contour(Image I);