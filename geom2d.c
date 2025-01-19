/****************************************************************************** 
  Implementation du module geom2d
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"geom2d.h"

Point set_point( double x, double y)
{
Point P = {x, y} ;
return P ;
}

Point add_point( Point P1, Point P2)
{
return set_point( P1.x+P2.x, P1.y+P2.y) ;
}

Vecteur vect_bipoint(Point A, Point B)
{
Vecteur V = {B.x-A.x, B.y-A.y} ;
return V;
}

Vecteur add_vect( Vecteur V1, Vecteur V2)
{
Vecteur V = {V1.x+V2.x, V1.y+V2.y};
return V ;
}

Point mult_point(Point P, int a){
  P.x = P.x*a;
  P.y = P.y*a;
  return P;
}

Vecteur mult_vect(Vecteur V, int a){
  V.x = V.x*a;
  V.y = V.y*a;
  return V;
}

double scalar_prod(Vecteur V1, Vecteur V2){
  double n = (V1.x*V2.x)+(V1.y+V2.y);
  return n;
}

double eucli_standard(Vecteur V){
  double n = sqrt(pow(V.x, 2) + pow(V.y, 2));
  return n;
}

double dist(Point P1, Point P2){
  double n = sqrt(pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2));
  return n;
}