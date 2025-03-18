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

Liste_Segment simplification_douglas_peucker(Liste_Point CONT, int j1, int j2, int d){
  Point Pj1;
  Point Pj2;
  int dmax=0;
  int dj;
  int k=j1;
  Liste_Segment L;
  Liste_Segment L1;
  Liste_Segment L2;
  Liste_Point CONT1=creer_liste_Point_vide();
  int c=0;
  for (int i=0;i<=j2;i++){
    if (i==j1){
      Pj1=CONT.first->data;
      c=1;
    }
    if (c==1){
      ajouter_element_liste_Point(CONT1,CONT.first->data);
    }
    CONT=supprimer_premier_element_liste_Point(CONT);
  }
  Pj2=CONT.last->data;
  Segment S=set_segment(Pj1,Pj2);
  for (int j=j1+1;j<j2;j++){
    dj=dist_point_seg(CONT1.first->data,Pj1,Pj2);
    if (dmax<dj){
      dmax=dj;
      k=j;
    }
  }
  if (dmax<=d){
    Segment S=set_segment(Pj1,Pj2);
    L.first->data=S;
  }
  else {
    L1=simplification_douglas_peucker(CONT, j1, k, d);
    L2=simplification_douglas_peucker(CONT, j2, k, d);
    L.first=L1.first;
    L.last=L2.first;
  }
  return L;
}