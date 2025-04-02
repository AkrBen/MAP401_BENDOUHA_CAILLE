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

typedef struct Tableau_Segment_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Segment *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Segment;

typedef struct Tableau_Bezier2_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Bezier2 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Bezier2;


Cellule_Liste_Point *creer_element_liste_Point(Point v);

Cellule_Liste_Segment *creer_element_liste_Segment(Segment v);

Liste_Point creer_liste_Point_vide();

Liste_Segment creer_liste_Segment_vide();

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

Liste_Segment ajouter_element_liste_Segment(Liste_Segment L, Segment e);

//ajouter_element_liste_Segment(Liste_Segment L, Segment e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

Liste_Point creer_liste_Bezier2_vide();
Liste_Point ajouter_element_liste_Bezier2(Liste_Bezier2 L, Bezier2 B2);
Liste_Point concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2);

//Liste_Segment creer_liste_Segment();
void ecrire_contour(Liste_Point L);

/*Simplification de Douglas-Peucker d'un contour de points*/
Liste_Point simplification_douglas_peucker(Tableau_Point CONT, int j1, int j2, double d);

