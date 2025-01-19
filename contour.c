#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "geom2d.h"
#include "image.h"
#include "exemple_sequence_point.c"
#include "contour.h"

Robot nouveauRobot(){
    Robot r;
    r.orientation=Est;
    r.position={0, 0};
    return r;
}
Contour calcul_ecriture_contour(Image I){
    int x,y;
    Robot r=nouveauRobot();
    int l=largeur_image(I);
    int h=hauteur_image(I);
    for (int i=0;i<l;i++){
        for (int j=0;j<h;j++){
            
        }
    }
}