/****************************************************************************** 
  Interface du module geom2d
******************************************************************************/
/*---- le type cellule de liste de point ----*/


typedef struct Vecteur_ 
{
double x , y ; /*coordonnees*/ 
} Vecteur ;

typedef struct Point_ 
{
double x , y ; /*coordonnees*/  
} Point ;

typedef struct Segment_
{
Point Px;
Point Py;
} Segment ;

typedef struct Cellule_Liste_Point_
{
	Point data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef struct Liste_Point_En_Chaine
{
	Liste_Point data;    /* donnee de l'element de liste */
	struct Liste_Point_En_Chaine* suiv; /* pointeur sur l'element suivant */
} Liste_Point_En_Chaine;

typedef struct Liste_de_liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Liste_Point_En_Chaine *first; /* pointeur sur le premier element de la liste */
	Liste_Point_En_Chaine *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_de_liste_Point;



typedef struct Cellule_Liste_Segment_
{
	Segment data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Segment_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Segment;

typedef struct Liste_Segment_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Segment *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Segment *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Segment;


typedef struct Bezier2_
{
Point C0;
Point C1;
Point C2;
} Bezier2 ;

typedef struct Cellule_Liste_Bezier2_
{
	Bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Bezier2_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Bezier2;

typedef struct Liste_Bezier2_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier2 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Bezier2 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier2;


typedef struct Bezier3_
{
Point C0;
Point C1;
Point C2;
Point C3;
} Bezier3 ;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/* cree le point de coordonnées (x,y) */  
Point set_point( double x, double y) ;

/* cree le segment de points Px et Py*/
Segment set_segment(Point Px, Point Py) ;

/* somme P1+P2 */ 
Point add_point(Point P1, Point P2) ;

/* vecteur correspondant au bipoint AB */ 
Vecteur vect_bipoint( Point A, Point B ) ;

/* somme V1+V2 */
Vecteur add_vect(Vecteur V1, Vecteur V2) ;

/* produit aP avec a un réel et P un point */
Point mult_point(Point P, int a);

/* produit aV avec a un réel et V un vecteur */
Vecteur mult_vect(Vecteur V, int a);

/* produit scalaire V1•V2 */
double scalar_prod(Vecteur V1, Vecteur V2);

/* Norme euclidienne (longueur) de V */
double eucli_standard(Vecteur V);

/* Distance entre deux points P1 et P2 */
double dist(Point P1, Point P2);

/* Distance entre un Point P et un segment [A,B] */
double dist_point_seg(Point P, Point A, Point B);

Point C_t_2(Bezier2 B2, double t);
Point C_t_3(Bezier3 B3, double t);

Bezier3 Bezier2_en_Bezier3(Bezier2 B2);

double dist_point_bezier2(Point P, Bezier2 B2, double t);

double dist_point_bezier3(Point P, Bezier3 B3, double t);

Bezier2 creation_Bezier2(Point P1,Point P2,Point P3);

Bezier3 creation_Bezier3(Point P1,Point P2,Point P3,Point P4);
