#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "contour.h"

int main(int argc, char* argv[]){
    Image I;
    I=lire_fichier_image(argv[1]);
    calcul_ecriture_contour(I);
    return 1;
}