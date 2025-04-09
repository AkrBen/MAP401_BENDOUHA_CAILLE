#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<image.h>
#include<approximation_bezier.h>

int main(int argc, char* argv[]){
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
    strcat(nom, "_bezier3.eps");
    fichier = fopen(nom, "w");
    if (fichier == NULL) {
        printf("Erreur: impossible de créer le fichier %s\n", nom);
        return -1;
    }

    fprintf(fichier, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fichier, "%%%%BoundingBox: 0 0 %d %d\n", l, h);
    fprintf(fichier, "0 setlinewidth\n");


    Liste_Point L;
    I = lire_fichier_image(argv[1]);
    Liste_de_liste_Point C = calcul_tous_contours(I);
    Liste_de_liste_Point CF;
    int nb_b=0;
    
    Tableau_tableau_Point C1 =sequence_de_sequence_points_liste_vers_tableau(C);
    int segments_total=0;
    int compt=0;

    for (int i = 0 ; i < C1.taille ; i++ ){
        Tableau_Point C2 = C1.tab[i];
        L = simplification_douglas_peucker_bezier3(C2,0 ,C2.taille-1,x);
        
        Tableau_Point T1 = sequence_points_liste_vers_tableau(L);
        printf("T1.taille = %d\n", T1.taille);
        nb_b=nb_b+(T1.taille)/4;
        Liste_Point LB3 = creer_liste_Point_vide();
        Cellule_Liste_Point *el0,*el1,*el2,*el3;

	    
        for( int u=0 ; u<(T1.taille)/4; u++){
            Bezier3 B3 = creation_Bezier3(T1.tab[u*4+0],T1.tab[u*4+1],T1.tab[u*4+2],T1.tab[u*4+3]);
            
            el0=creer_element_liste_Point(B3.C0);
            el1=creer_element_liste_Point(B3.C1);
            el2=creer_element_liste_Point(B3.C2);
            el3=creer_element_liste_Point(B3.C3);
            
            if (LB3.taille == 0){   
		        /* premier element de la liste */
                LB3.first = el0;
                LB3.first->suiv=el1;
                LB3.first->suiv->suiv=el2;
                LB3.first->suiv->suiv->suiv=el3;
                LB3.last = el3;
	        }else{
		        LB3.last->suiv = el0;
		        LB3.last->suiv->suiv = el1;
                LB3.last->suiv->suiv->suiv = el2;
                LB3.last->suiv->suiv->suiv->suiv = el3;
                LB3.last = el3;
            }
            LB3.taille= LB3.taille + 4;
        }
        Liste_Point_En_Chaine *elt;
	    elt=creer_element_liste_point_en_chaine(LB3);
	    if (CF.taille == 0)
	    {   
		
		    CF.first = CF.last = elt;
	    }
	    else
	    {
		    CF.last->suiv = elt;
		    CF.last = elt;
	    }
	    CF.taille++;
        segments_total=segments_total+compter_segments_contours(LB3);

    }
    
    Tableau_tableau_Point TP = sequence_de_sequence_points_liste_vers_tableau(CF);
    int nP = TP.taille;
    
    Point P,P2,P3,P4;

    for (int k =0 ; k< nP; k++){
        P = TP.tab[k].tab[0];
        
        fprintf(fichier, "%5.1f %5.1f moveto\n", P.x, h - P.y);

        int nP2=TP.tab[k].taille/4;
        for (int k1 =0 ; k1< nP2; k1++){
            
            P2 = TP.tab[k].tab[k1*4+1];
            P3 = TP.tab[k].tab[k1*4+2];
            P4 = TP.tab[k].tab[k1*4+3];
            fprintf(fichier, "%5.1f %5.1f %5.1f %5.1f %5.1f %5.1f curveto\n", P2.x, h - P2.y , P3.x, h - P3.y , P4.x, h - P4.y );

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
    printf("Cette image simplifiée a %d segments.\n",segments_total-compt);
    printf("nb courbes de bezier3 : %d \n",nb_b);
    
    return 0;
}
