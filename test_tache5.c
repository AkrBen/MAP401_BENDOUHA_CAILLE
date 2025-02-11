#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "contour.h"
//#include "image.h"

int main(int argc, char* argv[]){
    Image I;
    I=lire_fichier_image(argv[1]);
    calcul_tous_contours(I);
    return 1;
}