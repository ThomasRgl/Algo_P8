#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long int  ullint;

ullint rec_PT( size_t y, size_t x  ){
    if(x == 0 | x == y )
        return 1;
    return rec_PT( y - 1,  x  ) + rec_PT( y - 1, x - 1 );
}

ullint ite_tab_PT( size_t y, size_t x ){
    if(x > y)
        return 0;

    ullint** tab = malloc( (y + 1) * sizeof(ullint*) );
    // memset()
    ullint value = 0;
    for(size_t i = 0; i <= y; i++){
        tab[i] =  malloc( (x + 1) * sizeof(ullint) );
        for(size_t j = 0; j <= x; j++){
            if(i == 0 | j == 0 | i == j  )
                value = 1;
            else
                value = tab[i - 1][j] + tab[i - 1][j - 1];
            tab[i][j] = value;
        }
    }

    value = tab[y][x];
    for(size_t i = 0; i <= y; i++)
        free(tab[i]);

    free(tab);

    return value;

}

ullint ite_vect_PT( size_t y, size_t x ){
    if(x > y)
        return 0;

    ullint* tab = malloc( (x + 1) * sizeof(ullint*) );
    memset(tab, 0, (x + 1) * sizeof(ullint*));
    tab[0] = 1;
    ullint res;

    for( size_t i = 0; i < y; i++){
        for( size_t j = x ; j >= 1; j--){
            tab[j] = tab[ j ] + tab[ j - 1];
        }
    }
    res = tab[x];
    free(tab);
    return res;
}

ullint ite_incr_PT( size_t y, size_t x ){
    //
}

ullint fact(size_t x ){ //peut etre optimisée
    // printf("x %ld\n", x );
    ullint val = 1;
    for( int i = 1; i <= x; i++){
        // printf("aaa %ld\n", x );
        val*= i;
        }

    return val;
}

ullint factoriel_PT( size_t y, size_t x ){
    return fact(y) / (fact(x) * fact(y - x));
}

void test_func(){
    ullint res;
    clock_t t0, t1, dt;
    for( size_t n = 0; n <= 20; n+=1){
        printf ("y : %lu\tx :%lu \t\t", n*2, n );

        if ( n <= 10){
            t0 = clock();
            for(int j = 0; j != 100; j++)
                res = rec_PT(n * 2, n);
            t1 = clock();
            dt = t1 - t0;
            printf ("rec_PT : %d\t\t", (int) dt );
            }
        else
            printf ("rec_PT : ERROR  \t" );

        t0 = clock();
        for(int j = 0; j != 100; j++)
             ite_tab_PT(n * 2, n);
        t1 = clock();
        dt = t1 - t0;
        printf ("ite_tab_PT : %d \t", (int) dt );

        t0 = clock();
        for(int j = 0; j != 100; j++)
            res = ite_vect_PT(n*2 , n );
        t1 = clock();
        dt = t1 - t0;
        printf ("ite_vect_PT : %d \t", (int) dt );

        // t0 = clock();
        // for(int j = 0; j != 100; j++)
        //     res = ite_incr_PT(n, n * 2);
        // t1 = clock();
        // dt = t1 - t0;
        // printf ("ite_incr_PT : %d \t", (int) dt );


        if ( n <= 10){
            t0 = clock();
            for(int j = 0; j != 100; j++)
                factoriel_PT(n * 2, n );
            t1 = clock();
            dt = t1 - t0;
            printf ("factoriel_PT : %d \t", (int) dt );
            }
        else
            printf ("factoriel_PT : ERROR  \t" );



        printf("resultat : %llu", res );
        printf("\n");
    }
}

int main(){
    test_func();
    return 0;
}

// temps en milliseconde nécessaire pour calculer 100 fois la valeur (y,x) dans le triangle de pascal

// y : 0	x :0 		rec_PT : 5		    ite_tab_PT : 15 	ite_vect_PT : 9 	factoriel_PT : 7 	    resultat : 1
// y : 2	x :1 		rec_PT : 7		    ite_tab_PT : 42 	ite_vect_PT : 10 	factoriel_PT : 9 	    resultat : 2
// y : 4	x :2 		rec_PT : 20		    ite_tab_PT : 54 	ite_vect_PT : 16 	factoriel_PT : 10 	    resultat : 6
// y : 6	x :3 		rec_PT : 38	    	ite_tab_PT : 79 	ite_vect_PT : 25 	factoriel_PT : 13 	    resultat : 20
// y : 8	x :4 		rec_PT : 130		ite_tab_PT : 118 	ite_vect_PT : 37 	factoriel_PT : 15 	    resultat : 70
// y : 10	x :5 		rec_PT : 461		ite_tab_PT : 160 	ite_vect_PT : 52 	factoriel_PT : 18 	    resultat : 252
// y : 12	x :6 		rec_PT : 1682		ite_tab_PT : 212 	ite_vect_PT : 70 	factoriel_PT : 20     	resultat : 924
// y : 14	x :7 		rec_PT : 6433		ite_tab_PT : 279 	ite_vect_PT : 94 	factoriel_PT : 23     	resultat : 3432
// y : 16	x :8 		rec_PT : 9292		ite_tab_PT : 108 	ite_vect_PT : 38 	factoriel_PT : 9 	    resultat : 12870
// y : 18	x :9 		rec_PT : 29218		ite_tab_PT : 129 	ite_vect_PT : 47 	factoriel_PT : 9 	    resultat : 48620
// y : 20	x :10 		rec_PT : 107528		ite_tab_PT : 151 	ite_vect_PT : 57 	factoriel_PT : 10 	    resultat : 184756
// y : 22	x :11 		rec_PT : ERROR  	ite_tab_PT : 216 	ite_vect_PT : 68 	factoriel_PT : ERROR  	resultat : 705432
// y : 24	x :12 		rec_PT : ERROR  	ite_tab_PT : 247 	ite_vect_PT : 81 	factoriel_PT : ERROR  	resultat : 2704156
// y : 26	x :13 		rec_PT : ERROR  	ite_tab_PT : 279 	ite_vect_PT : 94 	factoriel_PT : ERROR  	resultat : 10400600
// y : 28	x :14 		rec_PT : ERROR  	ite_tab_PT : 310 	ite_vect_PT : 108 	factoriel_PT : ERROR  	resultat : 40116600
// y : 30	x :15 		rec_PT : ERROR  	ite_tab_PT : 393 	ite_vect_PT : 125 	factoriel_PT : ERROR  	resultat : 155117520
// y : 32	x :16 		rec_PT : ERROR  	ite_tab_PT : 445 	ite_vect_PT : 246 	factoriel_PT : ERROR  	resultat : 601080390
// y : 34	x :17 		rec_PT : ERROR  	ite_tab_PT : 528 	ite_vect_PT : 160 	factoriel_PT : ERROR  	resultat : 2333606220
// y : 36	x :18 		rec_PT : ERROR  	ite_tab_PT : 522 	ite_vect_PT : 196 	factoriel_PT : ERROR  	resultat : 9075135300
// y : 38	x :19 		rec_PT : ERROR  	ite_tab_PT : 570 	ite_vect_PT : 196 	factoriel_PT : ERROR  	resultat : 35345263800
// y : 40	x :20 		rec_PT : ERROR  	ite_tab_PT : 621 	ite_vect_PT : 224 	factoriel_PT : ERROR  	resultat : 137846528820

// /!\ ce code a été compilié avec l'option -g, et aucune option d'optisation
// gcc -g main.c -o main.o


// Pour chaque n profondeur, on cherche la ligne = profondeur / 2


//rec_PT : Récursive classique
// Pour chaque ligne suplementaire que l'on souhaite calculer, on double le temps de calcul ET l'espace mémoire
// On a donc une complexité O(2^n) en temps ET en espace
// en pratique on observe bien une multiplacation par 2 à chaque fois quoi l'on va chercher une colonne de plus en profondeur
// à partir de profondeur = 20 (et ligne = profondeur/2 ), on arrete de calculer le temps car il ne se compte plus en milli secondes mais en secondes


//ite_tab_PT : Itérative, dans un tableau
// Pour chaque n profondeur, on a en mémoire un tableau de n * (n/2)
// on a donc une complexité de O(n^2) environ en temps et en mémoire (plus précisement O(n * n/2 ))
// en pratique on retrouve ""environ""  x * x/2 = temps
//

//ite_vect_PT : Itérative, dans un vecteur
// Peut importe la profondeur n, on a un vecteur de taille n/2.
// en temps on fait le meme nombre de calcul que dans la fonction Itérative, mais dans un seul vecteur
// On a donc une complexité en temps de O(n * (n*2)) et en mémoire une complexité O(n / 2)
// en pratique on ne retrouve pas du tout ça et on retrouve un temps qui semble linéaire -> TODO

//ite_incr_PT : Itérative incrémentale
// non implementée -> TODO
//

// factoriel_PT :
// au dessus de profondeur = 20 on ne peut plus calculer car les résultats des factorielles est codé sur plus de 64 bits
// il va donc falloir trouver une formule qui ne demande pas de calculer de si gros nombres ou d'utiliser un u_int_128 pour pouvoir calculer de plus grosses factorielles
// sinon, en théorie on utilise une formule avec des factiorielles, factiorielle étant une fonction linéaire de complexité O(N), la formule à une complexité O(n)
// de plus cette formule semble avoir une complexité en espace constante donc O(1)
// en pratique on ne peut pas calculer très profond, et on obtient des resultats en temps contsant ce qui semble incohérent-> TODO


// TODO -> une version amélioré de cet exercice sera envoyée ce weekend
