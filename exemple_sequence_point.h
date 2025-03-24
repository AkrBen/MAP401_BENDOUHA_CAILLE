#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<geom2d.h>
/*---- le type Point et la fonction set_point ----*/
/* ou inclure le module de la tache 2             */



/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Point;

Cellule_Liste_Point *creer_element_liste_Point(Point v);

Liste_Point creer_liste_Point_vide();

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

//Liste_Segment creer_liste_Segment();
void ecrire_contour(Liste_Point L);

/*Simplification de Douglas-Peucker d'un contour de points*/
Liste_Segment simplification_douglas_peucker(Liste_Point CONT, int j1, int j2, int d);