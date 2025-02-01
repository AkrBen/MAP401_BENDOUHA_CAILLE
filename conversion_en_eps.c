#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "contour.h"


int main (int argc, char* argv[]){
    FILE * fichier;
    Image I;
    Contour C;

    if (argc !=3) {
        printf("Erreur: <fichier.pbm> + <stroke ou fill>\n");
        return -1;
    }

    fichier=fopen("fichier.eps","w");
     fprintf(fichier, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fichier, "%%BoundingBox: 0 0 500 500\n");
    fprintf(fichier, "0 setlinewidth\n");

    I = lire_fichier_image(argv[1]);
    C = calcul_ecriture_contour(I);

    Tableau_Point TP = sequence_points_liste_vers_tableau(C);
    int k;
    int nP = TP.taille;

    Point P = TP.tab[0];
    fprintf(fichier, "%5.1f %5.1f moveto\n", P.x, P.y);

    for (k = 1; k < nP; k++) {    
        P = TP.tab[k]; 
        fprintf(fichier, "%5.1f %5.1f lineto\n", P.x, P.y);
    } 

    if (strcmp(argv[2], "stroke") == 0) {
        fprintf(fichier, "stroke\n");
    } else if (strcmp(argv[2], "fill") == 0) {
        fprintf(fichier, "fill\n");
    }

    fprintf(fichier, "showpage\n");
    fclose(fichier);

    return 0;
}

