#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//#include "geom2d.h"
#include "image.h"
#include "exemple_sequence_point.h"

typedef enum {Nord , Est , Sud , Ouest } Orientation;

typedef struct{
    Orientation orientation;
    Point position;
} Robot;

Robot nouveauRobot();
Point avancer_inter(Robot r);
Robot avancer(Robot r);
Orientation tourner_90_degrees(Robot r);
Orientation tourner_270_degrees(Robot r);
Pixel valeur_pixel_gauche(Robot r, Image I);
Pixel valeur_pixel_droite(Robot r, Image I);
Orientation nouvelle_orientation(Robot r, Image I);
Liste_Point memoriser_position(Point p, Liste_Point L);
Contour calcul_ecriture_contour(Image I);
Image pixels_candidats(Image I);
int calcul_contour_a_partir_de_pixel(Image I, Image M, Point p);
void calcul_tous_contours(Image I);