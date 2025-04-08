#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<image.h>
#include<approximation_bezier.h>

int main(int argc, char* argv[]){
    Liste_Point L;
    Image I = lire_fichier_image(argv[1]);
    Liste_de_liste_Point C = calcul_tous_contours(I);
    Liste_de_liste_Point CF;
    
    
    Tableau_tableau_Point C1 =sequence_de_sequence_points_liste_vers_tableau(C);
    
    for (int i = 0 ; i < C1.taille ; i++ ){
        Tableau_Point C2 = C1.tab[i];
        printf("START\n");
        L = simplification_douglas_peucker_bezier2(C2,0 ,C2.taille-1,2);
        //
        Liste_Point_En_Chaine *el;

	    el=creer_element_liste_point_en_chaine(L);
	    if (CF.taille == 0)
	    {   
		    /* premier element de la liste */
		    CF.first = CF.last = el;
	    }
	    else
	    {
		    CF.last->suiv = el;
		    CF.last = el;
	    }
	    CF.taille++;
       

        ecrire_contour(L);
    }
    printf("OK\n");
    printf(" taille L3 = %d\n", CF.taille);





    printf("END\n");
    
    return 0 ;
}
