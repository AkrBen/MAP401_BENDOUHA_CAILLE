#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<contour.h>

int main (int argc, char* argv[]){
    Image I;
    I=lire_fichier_image(argv[1]);
    Liste_Point L=creer_liste_Point_vide();
    L=calcul_ecriture_contour(I);
    int x=atof(argv[2]);
    Liste_Segment L1;
    L1=simplification_douglas_peucker(L,10,50,x);
}