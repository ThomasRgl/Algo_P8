#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
Matrice
vacteur succeseur
liste successeurs
matrice compacte 
brins

ecrire les structures
ecrire fonction de transfert

*/



struct sommet {
    int num;
    float val;
    int nb_voisin;
    struct sommet ** voisin; 
};typedef struct sommet Sommet;

struct sommet2 {
    int num;
    float val;
    int nb_voisin;
    struct sommet2 ** voisin; 
};typedef struct sommet2 Sommet2;


struct matrice{
    int nbs;
    int * matriceVoisin;
};

//////////////////////////////
struct matrice{
    int nbs;
    int * matriceVoisin;
};
//////////////////////////////

struct triplet
{
    int i;
    int j;
    float val;
};

struct matriceCompacte{
    int nbs;
    int nba;
    struct triplet * vec;
};


//////////////////////////////

struct grlissue
{
    int nbs;
    struct sommet ** som;

};

struct sommet 
{
    char nom[20];
    int num;
    struct succ * succ;
};

struct Succ
{
    float val;
    struct  sommet * som;
    struct succ * next; 
};

//////////////////////////////

struct sommet{
    int num;
    int nbsucc;
    float * poids;
    struct sommet ** suc; 
};

//////////////////////////////


struct desbrins{
    short sommet;
    short brin_suivant;
    float poid ;
};

struct graphBrins{
    int nbs;
    int nbbr;
    short * sommets;
    struct debrins * bd;
};


Ecrire les 20 fonctions de transfere 
! !! ! ! !! ! ! ! !  !! ! !

Lire ennoncer projet 


//////////////////////////////1
int main(int argc, char const *argv[])
{
    
    return 0;
}

