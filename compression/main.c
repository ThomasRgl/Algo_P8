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

///////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////
// float * split_vect(size_t debut, size_t fin, float * vect, float * tmp );
// float * fusion_vect(size_t debut, size_t milieu, size_t fin, float * vect, float * tmp );

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
    }

    while( indexB != fin + 1 ){ //On colle de indexB à milieu
        tmp[tmpIndex] = vect[indexB];
        indexB++;
        tmpIndex++;
    }
    while(indexA != milieu + 1){//On colle de indexA à milieu
        tmp[tmpIndex] = vect[indexA];
        indexA++;
        tmpIndex++;
    }
    // printf("\n" );
    memcpy(vect + debut, tmp + debut,  ((fin - debut) + 1)  * sizeof(float) );
    return vect;
}

float * split_vect(size_t debut, size_t fin, float * vect, float * tmp ){
    if(fin - debut < 1)
        return vect;
    size_t milieu = debut + ((fin - debut) >> 1);
    vect = split_vect(debut, milieu, vect, tmp );
    vect = split_vect( milieu + 1 , fin, vect, tmp );
    return fusion_vect( debut, milieu, fin, vect, tmp);
}

void tri_fusion_vect(vec_t * vect){
    float * vectP = vect->v;
    float * tmp = malloc(vect->nbele * sizeof(float));
    memcpy(tmp, vectP, vect->nbele * sizeof(float) );
    vect->v = split_vect(0, vect->nbele - 1, vectP, tmp );
}

///////////////////////////////////////////////////////////////////////////


void tamiser(float * vect, size_t noeud, size_t n) {
    size_t k = noeud;
    size_t j = 2 * k;
    float tmp;
    while( j <= n){
        if(j < n && vect[j] < vect[j+1]){
            j++;
        }
        if( vect[k] < vect[j] ){
            tmp = vect[k];
            vect[k] = vect[j];
            vect[j] = tmp;
            k = j;
            j = 2 * k;
        }
        else{
            j = n + 1;
        }
    }
}

void triParTas(float * vect, size_t longueur){
    float tmp;
    for( int i = longueur >> 1; i >= 0; i--){
        tamiser(vect, i, longueur);
    }
    for( int i = longueur - 1; i >= 1; i--){
        tmp = vect[i];
        vect[i] = vect[0];
        vect[0] = tmp;
        tamiser(vect, 0, i-1);
    }
}

void tri_tas_vect( vec_t * vect ){
    triParTas(vect->v, vect->nbele);
}


///////////////////////////////////////////////////////////////////////////

int  partionner(float * vect, int deb, int fin, int pivot ){
    float tmp = vect[pivot];
    vect[pivot] = vect[fin];
    vect[fin] = tmp;

    int j = deb;
    for(int i = deb; i <= fin - 1; i++){
        if( vect[i] <= vect[fin]){
            tmp = vect[i];
            vect[i] = vect[j];
            vect[j] = tmp;

            j++;
        }
    }

    tmp = vect[fin];
    vect[fin] = vect[j];
    vect[j] = tmp;

    return j;

}

void triRapide( float * vect, int deb, int fin){
    if(deb < fin){
        int pivot = deb; // choix pivot
        pivot = partionner(vect, deb, fin, pivot);
        triRapide(vect, deb, pivot - 1 );
        triRapide(vect, pivot + 1 , fin );
    }
}

void tri_rapide_vect( vec_t * vect ){
    triRapide(vect->v, 0, vect->nbele - 1);
}


//////////////////////////////////////////////////////////////////////////


void dubious_random_vect_benchmark(char const *fileName ){


    FILE *fp;

    fp = fopen(fileName, "w");

    clock_t t0, t1, dt, t_null;
    vec_t vect;
    t0 = clock();
    t_null = t0 - t0;
    int nb_sample = 10;
    fprintf(fp,"x, tri à bulle, tri insertion, tri selection, tri fusion, tri tas, tri rapide\n");
    for(unsigned long long n = 16; n < 1000000 /*10^6*/; n *= 2){
        fprintf(fp,"%*lld,", 0, n );
        printf("%lld\n", n );


        //
        dt = t_null;
        for(int i = 0; i < nb_sample; i++ ){
            if(n > 10000){break;}
            vect = creeretremplir(n);
            t0 = clock();
            tri_bull_vect(&vect);
            t1 = clock();
            dt += t1 - t0;
            free(vect.v);
        }
        dt = dt/nb_sample;
        fprintf(fp, "%*d,", 0, (int) dt );

        //
        dt = t_null;
        for(int i = 0; i < nb_sample; i++ ){
            if(n > 20000){break;}
            vect = creeretremplir(n);
            t0 = clock();
            tri_insertion_vect(&vect);
            t1 = clock();
            dt += t1 - t0;
            free(vect.v);
        }
        dt = dt/nb_sample;
        fprintf(fp, "%*d,", 0, (int) dt );

        //
        dt = t_null;
        for(int i = 0; i < nb_sample; i++){
            if(n > 30000){break;}
            vect = creeretremplir(n);
            t0 = clock();
            tri_selection_vect(&vect);
            t1 = clock();
            dt += t1 - t0;
            free(vect.v);
        }
        dt = dt/nb_sample;
        fprintf(fp, "%*d,", 0, (int) dt );

        //
        dt = t_null;
        for(int i = 0; i < nb_sample; i++){
            vect = creeretremplir(n);
            t0 = clock();
            tri_fusion_vect(&vect);
            t1 = clock();
            dt += t1 - t0;
            free(vect.v);
        }
        dt = dt/nb_sample;
        fprintf(fp, "%*d,", 0, (int) dt );

        //
        dt = t_null;
        for(int i = 0; i < nb_sample; i++){
            vect = creeretremplir(n);
            t0 = clock();
            tri_tas_vect(&vect);
            t1 = clock();
            dt += t1 - t0;
            free(vect.v);
        }
        dt = dt/nb_sample;
        fprintf(fp, "%*d,", 0, (int) dt );

        //
        dt = t_null;
        for(int i = 0; i < nb_sample; i++){
            vect = creeretremplir(n);
            t0 = clock();
            tri_rapide_vect(&vect);
            t1 = clock();
            dt += t1 - t0;
            free(vect.v);
        }
        dt = dt/nb_sample;
        fprintf(fp, "%*d,", 0, (int) dt );



        //
        fprintf(fp, "\n");


    }
    printf("done\n");
    fclose(fp);
    return;


}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {

    // test_func();

    vec_t vect = creeretremplir(20);
    printVect(vect);

    //décommenter les tris pour tester

    // tri_bull_vect(&vect);
    // tri_insertion_vect(&vect);
    // tri_selection_vect(&vect);
    // tri_tas_vect(&vect);
    // tri_fusion_vect(&vect);
    tri_rapide_vect(&vect);
    printVect(vect);

    // passer un fichier en parametre pour lancer le benchmark sur les tris
    if(argc < 2){
        printf("ERROR - FICHIER MANQUANT\n");
        return 0 ;
    }
    if(argc >= 2){
        //
        dubious_random_vect_benchmark(argv[1]);
    }










    // cellfloat_t * head = creer(20);
    // printCells(head);




    return 0;
}
