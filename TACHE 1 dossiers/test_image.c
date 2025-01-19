#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"

int main(int argc, char* argv[]){
    Image I , A;
    if (argc !=2){
        printf("il faut mettre en argument un fichier image\n");
        return -1;
    }
    I = lire_fichier_image(argv[1]);
    printf("voici l'image sur l'écran :\n");
    ecrire_image(I);
    A = negatif_image(I);
     printf("voici l'image négative sur l'écran :\n");
    ecrire_image(A);

    return 0;
}
