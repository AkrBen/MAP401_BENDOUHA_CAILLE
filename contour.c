#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "contour.h"

Robot nouveauRobot(){
    Robot r;
    r.orientation=Est;
    r.position=set_point(0,0);
    return r;
}

Point avancer_inter(Robot r){
    switch (r.orientation){
        case Est:
            return set_point(r.position.x+1,r.position.y);
        case Ouest:
            return set_point(r.position.x-1,r.position.y);
        case Sud:
            return set_point(r.position.x,r.position.y+1);
        case Nord:
            return set_point(r.position.x,r.position.y-1);
    }
}

Robot avancer(Robot r){
    Robot r1=nouveauRobot();
    Point p=avancer_inter(r);
    r1.position=set_point(p.x,p.y); 
    r1.orientation=r.orientation;
    return r1;
}

Orientation tourner_90_degrees(Robot r){
    switch (r.orientation){
        case Est:
            r.orientation=Nord;
            break;
        case Ouest:
            r.orientation=Sud;
            break;
        case Sud:
            r.orientation=Est;
            break;
        case Nord:
            r.orientation=Ouest;
            break;
    }
    return r.orientation;
}

Orientation tourner_270_degrees(Robot r){
    r.orientation=tourner_90_degrees(r);
    r.orientation=tourner_90_degrees(r);
    r.orientation=tourner_90_degrees(r);
    return r.orientation;
}
Pixel valeur_pixel_gauche(Robot r, Image I){
    switch (r.orientation){
        case Est:
            return get_pixel_image(I,r.position.x+1,r.position.y);
        case Ouest:
            return get_pixel_image(I,r.position.x,r.position.y+1);
        case Nord:
            return get_pixel_image(I,r.position.x,r.position.y);
        case Sud:
            return get_pixel_image(I,r.position.x+1,r.position.y+1);
    }
}

Pixel valeur_pixel_droite(Robot r, Image I){
    switch (r.orientation){
        case Est:
            return get_pixel_image(I,r.position.x+1,r.position.y+1);
        case Ouest:
            return get_pixel_image(I,r.position.x,r.position.y);
        case Nord:
            return get_pixel_image(I,r.position.x+1,r.position.y);
        case Sud:
            return get_pixel_image(I,r.position.x,r.position.y+1);
    }
}

Orientation nouvelle_orientation(Robot r, Image I){
    Pixel Pg=valeur_pixel_gauche(r,I);
    Pixel Pd=valeur_pixel_droite(r,I);
    if (Pg==NOIR){
        r.orientation=tourner_90_degrees(r);
    }
    else if (Pd==BLANC){
        r.orientation=tourner_270_degrees(r);
    }
    return r.orientation;
}

Liste_Point memoriser_position(Point p, Liste_Point L){
    L=ajouter_element_liste_Point(L,p);
    return L;
}

Contour calcul_ecriture_contour(Image I){
    int segments=-1;
    int x0=0;
    int y0=0;
    Liste_Point L=creer_liste_Point_vide();
    Robot r=nouveauRobot();
    int l=largeur_image(I);
    int h=hauteur_image(I);
    for (int i=1;i<=l;i++){
        for (int j=1;j<=h;j++){
            if ((get_pixel_image(I,i,j)==NOIR)&&(get_pixel_image(I,i,j-1)==BLANC)){
                x0=i-1;
                y0=j-1;
                r.position=set_point(x0,y0);
                j=h;
                i=l;
            }
        }
    }
    int boucle=1;
    while(boucle==1){
        L=memoriser_position(r.position,L);
        segments++;
        r=avancer(r);
        r.orientation=nouvelle_orientation(r,I);
        if ((r.position.x==x0) && (r.position.y==y0) && (r.orientation==Est)){
            boucle=0;
        }
    }
    L=memoriser_position(r.position,L);
    ecrire_contour(L);
    segments++;
    printf("Ce contour est composé de %d segments\n", segments);
    return L;
}

Image pixels_candidats(Image I){
    int l=largeur_image(I);
    int h=hauteur_image(I);
    Image M=creer_image(l,h);
    for (int i=1;i<=l;i++){
        for (int j=1;j<=h;j++){
            if ((get_pixel_image(I,i,j)==NOIR)&&(get_pixel_image(I,i,j-1)==BLANC)){
                set_pixel_image(M,i,j,1);
            }
        }
    }
    
    return M;
}

Contour calcul_contour_a_partir_de_pixel(Image I, Image M, Point p){
    int segments=-1;
    Liste_Point L=creer_liste_Point_vide();
    Robot r=nouveauRobot();
    int x0=p.x-1;
    int y0=p.y-1;
    r.position=set_point(x0,y0);
    set_pixel_image(M,r.position.x+1,r.position.y+1,0);
    int boucle=1;
    while(boucle==1){
        L=memoriser_position(r.position,L);
        segments++;
        if (r.orientation==Est){
            set_pixel_image(M,r.position.x+1,r.position.y+1,0);
        }
        
        r=avancer(r);
        r.orientation=nouvelle_orientation(r,I);
        if ((r.position.x==x0) && (r.position.y==y0) && (r.orientation==Est)){
            boucle=0;
        }
    }
    L=memoriser_position(r.position,L);
    ecrire_contour(L);
    segments++;
    printf("Ce contour est composé de %d segments\n", segments);
    return L;
}

int compter_segments_contours(Contour L){
    int x=0;
    Cellule_Liste_Point *el = L.first;
    while (el) {
		x++;
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
    return x;
}

Liste_de_liste_Point calcul_tous_contours(Image I){
    //Cellule_Liste_Point contours[100];
    Image M=pixels_candidats(I);
    int l=largeur_image(M);
    int h=hauteur_image(M);
    int c=0;
    int segments_total=0;
    Liste_de_liste_Point L1=creer_liste_de_liste_Point_vide();
     for (int i=1;i<=l;i++){
        for (int j=1;j<=h;j++){
            if (get_pixel_image(M,i,j)==NOIR){
                Point p=set_point(i,j);
                Liste_Point L=creer_liste_Point_vide();
                L=calcul_contour_a_partir_de_pixel(I,M,p);
                segments_total=segments_total+compter_segments_contours(L);
                //if (c>0){
                    //Liste_Point L2=creer_liste_Point_vide();
                    ajouter_element_liste_de_liste_Point(L1, L);
                    //printf("L1: %d\n",c);
                    //ecrire_contour(L1);
                //}
                //Liste_Point L1=creer_liste_Point_vide();
                //L1=L2;
                //*contours[c]=L.first;
                c++;
            }
        }
    }
    printf("\nCette image a %d contours.\n",c);
    printf("Cette image a %d points.\n",segments_total);
    printf("Cette image a %d segments.\n",segments_total-c);
    //ecrire_contour(L1);
    return L1;
}
