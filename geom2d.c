/****************************************************************************** 
  Implementation du module geom2d
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"exemple_sequence_point.h"

Point set_point( double x, double y)
{
Point P = {x, y} ;
return P ;
}

Segment set_segment(Point Px, Point Py){
  Segment S;
  S.Px=Px;
  S.Py=Py;
  return S;
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
  double n = (V1.x*V2.x)+(V1.y*V2.y);
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

double dist_point_seg(Point P, Point A, Point B){

  if (A.x == B.x && A.y == B.y) {
    return dist(P,A);
  }

  Vecteur AB = vect_bipoint(A, B);
  Vecteur AP = vect_bipoint(A, P);

  double AB_AB = scalar_prod(AB, AB);
  double AP_AB = scalar_prod(AP, AB);
  double lambda = AP_AB / AB_AB;

  if (lambda < 0) {
    return dist(A,P); 

  } else if (lambda > 1) {
    return dist(B,P); 

  } else {
  Point Q = set_point(A.x + lambda * AB.x, A.y + lambda * AB.y);
  return dist(Q,P); 
}
}

Bezier2 creation_Bezier2(Point P1,Point P2,Point P3){
    Bezier2 B2;
    B2.C0 = P1;
    B2.C1 = P2;
    B2.C2 = P3;
    return B2;
}

Bezier3 creation_Bezier3(Point P1,Point P2,Point P3,Point P4){
  Bezier3 B3;
  B3.C0 = P1;
  B3.C1 = P2;
  B3.C2 = P3;
  B3.C3 = P4;
  return B3;
}

Point C_t_2(Bezier2 B2, double t){
  Point P;
  double x,y;
  x = pow((1-t),2)*B2.C0.x+ 2*t*(1-t)*B2.C1.x + pow(t,2)*B2.C2.x;
  y = pow((1-t),2)*B2.C0.y+ 2*t*(1-t)*B2.C1.y + pow(t,2)*B2.C2.y;
  P = set_point(x,y);
  return P;
}

Point C_t_3(Bezier3 B3, double t){
  Point P;
  double x,y;
  x= pow((1-t),3)*B3.C0.x+ 3*t*pow((1-t),2)*B3.C1.x + 3*pow(t,2)*(1-t)*B3.C2.x + pow(t,3)*B3.C3.x;
  y= pow((1-t),3)*B3.C0.y+ 3*t*pow((1-t),2)*B3.C1.y + 3*pow(t,2)*(1-t)*B3.C2.y + pow(t,3)*B3.C3.y;
  P = set_point(x,y);
  return P;
}

Bezier3 Bezier2_en_Bezier3(Bezier2 B2){
  Bezier3 B3;
  B3.C0.x = B2.C0.x;
  B3.C1.x = (B2.C0.x+(B2.C1.x)*2)/3;
  B3.C2.x = (B2.C2.x+(B2.C1.x)*2)/3;
  B3.C3.x = B2.C2.x;

  B3.C0.y = B2.C0.y;
  B3.C1.y = (B2.C0.y+(B2.C1.y)*2)/3;
  B3.C2.y = (B2.C2.y+(B2.C1.y)*2)/3;
  B3.C3.y = B2.C2.y;
  return B3;
}

double dist_point_bezier2(Point P, Bezier2 B2, double t){
  Point P1 = C_t_2(B2,t);
  double d = dist(P,P1);
  return d;
}

