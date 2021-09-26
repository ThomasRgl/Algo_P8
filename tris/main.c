#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct cellfloat {
  float v;
  struct cellfloat * nxt;
} ;
typedef struct cellfloat cellfloat_t;
typedef struct cellfloat * liste;

liste creer (int nb) {
  liste tete, crt;
  int i;
  float x, y, z;
  if (nb < 2)
	nb = 10;
  tete = NULL;
  x = 1.0;
  y = 0.13;
  z = 0.021;
  for (i = 0; i < nb; i++) {
    crt = malloc (sizeof (cellfloat_t));
    assert (crt);
    crt->v   = x;
    crt->nxt = tete;
    tete     = crt;
    x += y;
    y += z;
    if (x > 1.5) {
      x -= 1.01;
    }
    if (x < 0.5) {
      x += 0.499;
    }
    if (y > 1.) {
      y = y - 1.01;
    }
    if (x < 0.5) {
      y += 0.5001;
    }
  }
  return tete;
}

void printCells(cellfloat_t * head){
    cellfloat_t * body = head;
    while( body ){
        printf("%f ", body->v);
        body = body->nxt;
    }
    printf("\n" );
}

struct vecfloat {
  int nbele;
  float * v;
} ;
typedef struct vecfloat vec_t;

vec_t creeretremplir (int nb) {
  vec_t w;
  int i;
  float x, y, z, *pt;
  if (nb < 2)
	nb = 10;
  w.nbele = nb;
  w.v = (float *) malloc (nb * sizeof(float));
  assert(w.v);
  x = 1.0;
  y = 0.13;
  z = 0.021;
  pt = w.v;
  for (i = 0; i < nb; i++) {
	*pt++ = x;
	x += y;
	y += z;
	if (x > 1.5) {
	  x -= 1.01;
	}
	if (x < 0.5) {
	  x += 0.499;
	}
	if (y > 1.) {
	  y = y - 1.01;
	}
	if (x < 0.5) {
	  y += 0.5001;
	}
  }
  return w;
}

void printVect(vec_t vect){
    for( int i = 0; i < vect.nbele; i++)
        printf("%f ", vect.v[i]);

    printf("\n" );
}


///////////////////////////////////////////////////////////////////////////

void tri_bull_vect(vec_t * vect){
    float tmp = 0;
    for( size_t i = vect->nbele - 1; i >= 1; i-- ){
        for( size_t j = 0; j < i; j++ ){
            if( vect->v[j + 1] < vect->v[j] ){
                tmp = vect->v[j + 1];
                vect->v[j + 1] = vect->v[j];
                vect->v[j] = tmp;
            }
        }
    }
}

void tri_selection_vect(vec_t * vect){
    int n = vect->nbele;
    size_t min = 0;
    float tmp = 0;
    for(size_t i = 0; i <= n - 2; i++ ){
        min = i;
        for( size_t j = i + 1; j < n; j++){
            if( vect->v[min] > vect->v[j])
                min = j;
        }
        if(min != i){
            tmp = vect->v[i];
            vect->v[i] = vect->v[min];
            vect->v[min] = tmp;
        }
    }
}

void tri_insertion_vect(vec_t * vect){
    int n = vect->nbele;
    size_t index = 0;
    float tmp = 0;
    for(size_t i = 1; i < n; i++ ){
        tmp = vect->v[i];
        index = i;
        while( tmp < vect->v[index - 1] && index > 0 ){
            // printf("aa\n" );
            vect->v[index] = vect->v[index - 1];
            index --;
        }
        vect->v[index] = tmp;
    }
}

float * split_vect(size_t debut, size_t fin, float * vect, float * tmp );
float * fusion_vect(size_t debut, size_t milieu, size_t fin, float * vect, float * tmp );

void tri_fusion_vect(vec_t * vect){
    float * vectP = vect->v;
    float * tmp = malloc(vect->nbele * sizeof(float));
    memcpy(tmp, vectP, vect->nbele * sizeof(float) );
    vect->v = split_vect(0, vect->nbele - 1, vectP, tmp );
}

float * split_vect(size_t debut, size_t fin, float * vect, float * tmp ){
    if(fin - debut < 1)
        return vect;
    size_t milieu = debut + ((fin - debut) >> 1);
    // printf("split with %ld %ld \n",debut, milieu );
    vect = split_vect(debut, milieu, vect, tmp );
    // printf("split with %ld %ld \n",milieu + 1 , fin );
    vect = split_vect( milieu + 1 , fin, vect, tmp );
    // printf("glue with %ld %ld %ld \n",debut ,milieu, fin );
    return fusion_vect( debut, milieu, fin, vect, tmp);
}

float * fusion_vect(size_t debut, size_t milieu, size_t fin, float * vect, float * tmp ){
    size_t indexA = debut;
    size_t indexB = milieu + 1;
    size_t tmpIndex = debut;
    while(indexA != milieu + 1 && indexB != fin + 1 ){
        if(vect[indexA] < vect[indexB]){
            tmp[tmpIndex] = vect[indexA];
            indexA++;
            tmpIndex++;
        }
        else{
            tmp[tmpIndex] = vect[indexB];
            indexB++;
            tmpIndex++;
        }
        // printf("%f - ", tmp[tmpIndex - 1] );
    }
    // printf(" end " );
    while( indexB != fin + 1 ){ //On colle de indexB à milieu
        // printf(" colleB " );
        tmp[tmpIndex] = vect[indexB];
        indexB++;
        // printf("%f - ", tmp[tmpIndex] );
        tmpIndex++;
    }
    while(indexA != milieu + 1){//On colle de indexA à milieu
        // printf(" colleA " );
        tmp[tmpIndex] = vect[indexA];
        indexA++;
        // printf("%f - ", tmp[tmpIndex] );
        tmpIndex++;
    }
    // printf("\n" );
    memcpy(vect, tmp,  20 * sizeof(float) );
    return vect;
}


// fonction fusionner(p, P, q, Q)
//     pour i allant de 0 à taille(p)-1 faire
//         si valeur(p.suivant) > valeur(q.suivant)
//             déplacer le maillon q.suivant après le maillon p
//             si Q = 1 quitter la boucle
//             Q := Q-1
//         sinon
//             si P = 1
//                 tant que Q >= 1
//                     q := q.suivant
//                     Q := Q-1
//                 fin
//                 quitter la boucle
//             fin
//             P := P-1
//         fin
//         p := p.suivant
//     fin
//     renvoyer q
// fin
//

void tri_tas_vect(){}

void tri_rapide_vect(){}



int main (){
    vec_t vect = creeretremplir(20);
    printVect(vect);

    // tri_bull_vect(&vect);
    tri_fusion_vect(&vect);
    printVect(vect);



    // cellfloat_t * head = creer(20);
    // printCells(head);




    return 0;
}
