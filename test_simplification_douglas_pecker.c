#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<contour.h>

int main (int argc, char* argv[]){
    FILE *fichier;
    Image I;
    int x=atof(argv[2]);
    if (argc != 4) {
        printf("Erreur: <fichier.pbm> <stroke ou fill>\n");
        return -1;
    }
    I=lire_fichier_image(argv[1]);
    UINT h = hauteur_image(I);
    UINT l = largeur_image(I);
    char nom[1000];

    int i;
    for (i = 0; i < strlen(argv[1]) - 4; i++) {
        nom[i] = argv[1][i];
    }
    nom[i] = '\0'; 
    strcat(nom, "_");
    strcat(nom, argv[3]);
    strcat(nom, "_d");
    strcat(nom,argv[2]);
    strcat(nom, ".eps");
    fichier = fopen(nom, "w");
    if (fichier == NULL) {
        printf("Erreur: impossible de créer le fichier %s\n", nom);
        return -1;
    }

    fprintf(fichier, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fichier, "%%%%BoundingBox: 0 0 %d %d\n", l, h);
    fprintf(fichier, "0 setlinewidth\n");

    Liste_de_liste_Point L_total;
    L_total=calcul_tous_contours(I);
    //printf("Taille de L_total:%d \n", L_total.taille);

    Tableau_tableau_Point T_total=sequence_de_sequence_points_liste_vers_tableau(L_total);

    Liste_de_liste_Point L_simpli=creer_liste_de_liste_Point_vide();
    int nP=T_total.taille;
    

    int segments_total=0;
    for (int j =0 ; j< nP; j++){
        int nP1 = T_total.tab[j].taille;
        Liste_Point L3 = simplification_douglas_peucker(T_total.tab[j],0,nP1-1,x);
        Liste_Point_En_Chaine *el;

        el=creer_element_liste_point_en_chaine(L3);
        if (L_simpli.taille == 0)
        {
            /* premier element de la liste */
            L_simpli.first = L_simpli.last = el;
        }
        else
        {
            L_simpli.last->suiv = el;
            L_simpli.last = el;
        }
        L_simpli.taille++;
        segments_total=segments_total+compter_segments_contours(L3);
     }
 

    Tableau_tableau_Point TP = sequence_de_sequence_points_liste_vers_tableau(L_simpli);
    nP = TP.taille;
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

    if (strcmp(argv[3], "stroke") == 0) {
        fprintf(fichier, "stroke\n");
    } else if (strcmp(argv[3], "fill") == 0) {
        fprintf(fichier, "fill\n");
    } else {
        printf("Erreur: argument incorrect, utiliser 'stroke' ou 'fill'\n");
        fclose(fichier);
        return -1;
    }

    fprintf(fichier, "showpage\n");
    fclose(fichier);

    printf("Cette image simplifiée a %d points.\n",segments_total);
    printf("Cette image simplifiée a %d segments.\n",segments_total-nP);
    return 0;
}