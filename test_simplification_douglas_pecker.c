#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<contour.h>

int main (int argc, char* argv[]){
    FILE *fichier;
    Image I;
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
    Liste_Point L=creer_liste_Point_vide();
    L=calcul_ecriture_contour(I);
    Tableau_Point L2=sequence_points_liste_vers_tableau(L);
    int x=atof(argv[2]);
    Liste_Point L1;
    Liste_de_liste_Point L_total;
    L1=simplification_douglas_peucker(L2,0,L2.taille,x);

    Tableau_Point TP = sequence_points_liste_vers_tableau(L1);
    int k = 0;
    int nP = TP.taille;
    Point premier_point, P;

    //printf("Contour avec %d points.\nCe contour est composé de %d segments\n",nP,nP-1);

    while (k < nP) {
        P = TP.tab[k];
        premier_point = P;
        fprintf(fichier, "%5.1f %5.1f moveto\n", P.x, h - P.y);
        k++;

        while (k < nP) {
            P = TP.tab[k];
            fprintf(fichier, "%5.1f %5.1f lineto\n", P.x, h - P.y);
            k++;

            if (P.x == premier_point.x && P.y == premier_point.y) {
                break;
            }
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

    L_total=calcul_tous_contours(I);
    Tableau_Point T_total=sequence_de_sequence_points_liste_vers_tableau(L_total);
    nP=T_total.taille;
    int j=1;
    int c=1;
    int compt=0;
    Point Debut=T_total.tab[0];
    Tableau_Point T_inter;
    T_inter.tab = malloc(100000000 * sizeof(Point));
    T_inter.taille=0;
    int segments_total=0;
    while(j<nP){
        T_inter.taille++;
        T_inter.tab[c]=T_total.tab[j];
        c++;
        if ((Debut.x==T_total.tab[j].x)&&(Debut.y==T_total.tab[j].y)){
            Liste_Point L3=creer_liste_Point_vide();
            L3=simplification_douglas_peucker(T_inter,0,T_inter.taille,x);
            compt++;
            segments_total=segments_total+compter_segments_contours(L3);
            T_inter.taille=0;
            c=0;
        }
        else if (c==1){
            Debut=T_total.tab[j];
        }
        j++;
    }
    printf("Cette image simplifiée a %d points.\n",segments_total);
    printf("Cette image simplifiée a %d segments.\n",segments_total-compt);
    return 0;
}