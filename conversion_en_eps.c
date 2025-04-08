#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "contour.h"

int main(int argc, char *argv[]) {
    FILE *fichier;
    Image I;
    Liste_de_liste_Point C;

    if (argc != 3) {
        printf("Erreur: <fichier.pbm> <stroke ou fill>\n");
        return -1;
    }

    I = lire_fichier_image(argv[1]);

    UINT h = hauteur_image(I);
    UINT l = largeur_image(I);
    char nom[1000];

    int i;
    for (i = 0; i < strlen(argv[1]) - 4; i++) {
        nom[i] = argv[1][i];
    }
    nom[i] = '\0'; 
    strcat(nom, "_");
    strcat(nom, argv[2]);
    strcat(nom, ".eps");

    fichier = fopen(nom, "w");
    if (fichier == NULL) {
        printf("Erreur: impossible de créer le fichier %s\n", nom);
        return -1;
    }

    fprintf(fichier, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fichier, "%%%%BoundingBox: 0 0 %d %d\n", l, h);
    fprintf(fichier, "0 setlinewidth\n");

    C = calcul_tous_contours(I);
    Tableau_tableau_Point TP = sequence_de_sequence_points_liste_vers_tableau(C);
    int nP = TP.taille;
   
    Point P;

    for (int k =0 ; k< nP; k++){
        P = TP.tab[k].tab[0];
        int nP2=TP.tab[k].taille;
        fprintf(fichier, "%5.1f %5.1f moveto\n", P.x, h - P.y);

        for (int k1 =1 ; k1< nP2; k1++){
            P = TP.tab[k].tab[k1];
            fprintf(fichier, "%5.1f %5.1f lineto\n", P.x, h - P.y);

        }
        fprintf(fichier, "\n");
    }
    

    if (strcmp(argv[2], "stroke") == 0) {
        fprintf(fichier, "stroke\n");
    } else if (strcmp(argv[2], "fill") == 0) {
        fprintf(fichier, "fill\n");
    } else {
        printf("Erreur: argument incorrect, utiliser 'stroke' ou 'fill'\n");
        fclose(fichier);
        return -1;
    }

    fprintf(fichier, "showpage\n");
    fclose(fichier);

    return 0;
}
