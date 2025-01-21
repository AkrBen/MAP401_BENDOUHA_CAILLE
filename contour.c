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

void avancer(Robot r){
    switch (r.orientation){
        case Est:
            r.position=

    }
}
Contour calcul_ecriture_contour(Image I){
    int x,y;
    Robot r=nouveauRobot();
    int l=largeur_image(I);
    int h=hauteur_image(I);
    for (int i=0;i<l;i++){
        for (int j=0;j<h;j++){
            if ((get_pixel_image(I,i,j)==NOIR)&&(get_pixel_image(I,i,j-1)==BLANC)){
                int x0=i-1;
                int y0=j-1;
                r.position={x0,y0};
                Point P_initial=r.position;
                j=h;
                i=l;
            }
        }
    }
    x=x0;
    y=y0;
    int boucle=1;
    while(boucle){
        
    }
}