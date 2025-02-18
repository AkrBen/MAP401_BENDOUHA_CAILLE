#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "contour.h"
//#include "image.h"

int main(int argc, char* argv[]){
    Image I;
    I=lire_fichier_image(argv[1]);
    Liste_Point L=creer_liste_Point_vide();
    L=calcul_tous_contours(I);
    //ecrire_contour(L);
    return 1;
}
