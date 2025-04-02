#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<image.h>
#include<approximation_bezier.h>

int main(int argc, char* argv[]){
    Image I = lire_fichier_image(argv[1]);
    Contour C = calcul_ecriture_contour(I);

    Bezier2 B2 = approx_bezier2(C, 0 ,C.taille-1 );

    //simplification_douglas_peucker_bezier2(C,0 ,C.taille-1,2);
    //ecrire_contour(L);

    printf("C0 = (%lf,%lf) ; C1 = (%lf,%lf) ; C2 = (%lf,%lf) \n",B2.C0.x,B2.C0.y,B2.C1.x,B2.C1.y,B2.C2.x,B2.C2.y);
    return 0 ;
}
