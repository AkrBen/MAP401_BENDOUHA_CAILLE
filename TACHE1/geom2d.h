/****************************************************************************** 
  Interface du module geom2d
******************************************************************************/


typedef struct Vecteur_ 
{
double x , y ; /*coordonnees*/ 
} Vecteur ;

typedef struct Point_ 
{
double x , y ; /*coordonnees*/  
} Point ;

/* cree le point de coordonnées (x,y) */  
Point set_point( double x, double y) ;

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



