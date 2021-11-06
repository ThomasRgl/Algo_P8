#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>




struct arbre{
    int num;
    float val;
    struct arbre * gauche;
    struct arbre * droite;
};

// typedef struct noeud noeud_t;
typedef struct arbre Arbre;


void affiche( Arbre * a ){
    if(!a)
        return;
    printf("a : %d %f `\n", a->num, a->val);
    affiche(a->gauche);
    affiche(a->droite);
    
}




int  appartient( Arbre * a, int nb){
    if( !a )
        return 0;
    if( a->num == nb )
        return 1; 
    
    if( appartient(a->gauche, nb)) 
        return 1;
    else if ( appartient(a->droite, nb) )
        return 1;
    else 
        return 0;
}

struct arbrev2{
    int num;
    float val;
    short gauche;
    short droite;
}; // 

// typedef struct noeud noeud_t;
typedef struct arbrev2 ArbreV2;

struct arbre2Vect{
    int nbn;
    ArbreV2 * vect;
};// On a un arbre compacte, donc plus rapide d'acces, les adresses sont stockées sur 8 bytes , avec le short on gagne 6 bytes d'espace par fils
//et àa facilite le parcours en largeur de l'arbre 
typedef struct arbre2Vect Arbre2Vect;


// arbres ternaires
struct arbrev3{
    int num;
    float val;
    short gauche;
    short milieu;
    short droite;
}; // 

// typedef struct noeud noeud_t;
typedef struct arbrev3 ArbreV3;

struct arbre3Vect{
    int nbn;
    ArbreV3 * vect;
};// 
typedef struct arbre3Vect arbre3Vect;


void/* ArbreV2 * */ convertToV2(Arbre * a){
    //TODO 
    // return ArbreV2 ;
}

void afficheV2( ArbreV2 * a ){
    //TODO 

    // if(!a)
    //     return;
    // printf("a : %d %f `\n", a->num, a->val);
    // affiche(a->gauche);
    // affiche(a->droite);
    
}

int  appartientV2( ArbreV2 * a, int nb){
    //TODO 

    // if( !a )
    //     return 0;
    // if( a->num == nb )
    //     return 1; 
    
    // if( appartient(a->gauche, nb)) 
    //     return 1;
    // else if ( appartient(a->droite, nb) )
    //     return 1;
    // else 
    //     return 0;
}

//////////////////////////////////////////////
# define N 8 /* OCTREE */
struct narbre{
    int num;
    float val;
    struct narbre * fils[N];
}; typedef struct narbre Narbre;

int  Nappartient( Narbre * a, int nb){
    if( !a )
        return 0;
    if( a->num == nb )
        return 1; 
    
    for(int i = 0; i < N; i++) {
        if( Nappartient(a->fils[i], nb) )
            return 1;
    }
    return 0;
}



int main(int argc, char const *argv[])
{
    
    return 0;
}
