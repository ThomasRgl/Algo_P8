#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void resetTab( long * tab, long size ){
    for( long i = 0; i < size; i++ ){
        tab[i] = 0;
    }
}

void affiche ( long * tab, long size){
    long boost = 0;
    long y = 0;
    long y_prev = 0;
    
    for( long i = 0; i <= size; i++ ){
        y = tab[i];
        if(y < y_prev){
            boost+=y_prev;
            }
        printf("%*s\n", (int) (y+1+boost) ,"X");
        y_prev = y;
    }
    printf("\n\n");
    
}

void affiche2 ( long * tab, long size){
    
    long y = 0;
    long i = 0;
    long i2 = 0;
    
    // return;
    while(  i <= size ){
        // printf("%ld\n", tab[i]) ;
        // i++;
        for(long j = 0; j < tab[i2]; j++){
            printf("%*s\n", (int) (y+1) ,"X");
            i++;
        }
        if(tab[i2] == 0){
            return;
        }
        i2++;
        y++;
        
    }
    printf("\n\n");
    
}

void affiche3 ( long * tab, long size){
    
    long y = 0;
    long i = 0;
    long i2 = 0;
    
    // return;
    while(  i <= size ){
        printf("%ld\n", tab[i]) ;
        
        
        i++;
        
    }
    printf("\n\n");
    
}

void forceUse( long * tab, long xmax){
    int randomValue = (int)(rand() / (double)RAND_MAX * (xmax));
    fprintf( stderr, "- %ld", tab[randomValue]);
}
//////////////////////////////////////////////////////////////////////////

// void droite (int x0, int y0, int x1, int y1) {
//   int x, y;
//   float yf;

//   for (x = x0; x <= x1; x++) {
//      yf = (float) (x - x0) * (y1 - y0);
//      yf /= (x1 - x0);
//      yf += y0;
//      y = (int) (yf + 0.5); /* approximation à l’entier le plus proche*/
//      affiche(x,y);
//   }
// }

//////////////////////////////////////////////////////////////////////////

void droite_br (long u, long v, long * tab) {
/* u est dx, v est dy */
   long x, y, delta, incD, incH;

   incH   = v << 1;
   delta  = incH - u;
   incD   = delta - u;
   for (x = 0, y = 0; x < u; x++) {
      // affiche(x, y);
      tab[x] = y;
      if (delta > 0) {
         y++;
         delta += incD;
      }
      else {
         delta += incH;
      }
   }
}



//////////////////////////////////////////////////////////////////////////

void droite_2p (long u, long v, long * tab) {
/* u est dx, v est dy */
    long x, y, delta, incD, incH;

    incH   = v << 1;
    delta  = incH - u;
    incD   = delta - u;
    x =0;
    y =0;

    while (x < u ) {
        if(delta > 0){
            if (delta - incH > 0 ){
                y++;
                tab[x] = y;
                x++;
                tab[x] = y;
                x++;
            }
            else{
                tab[x] = y;
                x++;
                y++;
                tab[x] = y;
                x++;
            }
            delta += incH + incD;
        }
        else{
            tab[x] = y;
            x++;
            tab[x] = y;
            x++;
            delta += incH * 2;
        }
        
   }

   if( (u-1)%2 && x < u){
        tab[x] = y;
   }
}



//////////////////////////////////////////////////////////////////////////

void droite_sym_2p (long u, long v, long * tab) {

}

// void droite_sym_2p_debug (long dx, long dy) {
    
//     long x1, x2, y1, y2, xend, leftover, incr2, c, incr1, D;

//     xend = (dx - 1) / 2;
//     leftover = (dx - 1) % 4;
//     incr2 = 4 * dy - 2 * dx;

//     affiche(0,0);
//     affiche(dx,dy);

//     c = 2 * dy;
//     incr1 = 2 * c;
//     D = incr1 - dx;
    
//     for (x1 = 1, x2 = dx - 1, y1 = 0, y2 = dy; x1 <= xend ; x1+=2, x2-=2 ) {
//         if(D < 0) {
//             //Patern1 F
//             affiche( x1 - 1, y1 );
//             affiche( x1, y1 );


//             //Patern1 B
//             affiche( x2, y2 );
//             affiche( x2 - 1, y2 );


//             D += incr1;
//         }
//         else{ 
//             if ( D < c ) {
//                 if( D == 0 ) {
//                     //Patern 2 F
//                     affiche( x1 - 1, y1 );
//                     y1++;
//                     affiche( x1, y1 ); 

//                     //Patern 1 B
//                     affiche( x2, y2 );
//                     affiche( x2 - 1, y2 );
//                 }
//                 else {
//                     //Patern 2 F
//                     affiche( x1 - 1, y1 );
//                     y1++;
//                     affiche( x1, y1 ); 

//                     //Patern 2 B
//                     affiche( x2, y2 );
//                     y2--; 
//                     affiche( x2 - 1, y2 );
//                 }
//             }
//             else if (D == c) {
//                 //Patern 3 F
//                 y1++;
//                 affiche( x1 - 1, y1 );
//                 affiche( x1, y1 ); 

//                 //Patern 2 B
//                 affiche( x2, y2 );
//                 y2--; 
//                 affiche( x2 - 1, y2 );
            
//             }
//             else {
//                 //Patern 3 F
//                 y1++;
//                 affiche( x1 - 1, y1 );
//                 affiche( x1, y1 ); 

//                 //Patern 3 B
//                 y2--;    
//                 affiche( x2, y2 );
//                 affiche( x2 - 1, y2 );
//             }
//             D += incr2;
//         }
//     }

//     if( leftover > 0 ){
//         // affiche( x2, y2 );
//         // affiche( x2 - 1, y2 );
//         // 2 from forward
//         // 1 from backward
//     }

//     return;
// }

//////////////////////////////////////////////////////////////////////////

void droite_3p( long dx, long dy, long * tab){
    long incr1, incr2, incr3, D, x, y, xend, c;

    x = 0;
    y = 0; 

    xend = dx - 1;
    tab[x] = y;
    incr2 = 4 * dy - 2 * dx;
    if( incr2 <= 0 ){ //slope <= 1/2
        c = 2 * dy;
        incr1 = 2 * c;
        incr3 = incr2 + c;
        D = incr1 - dx;
        while (x < xend){
            if( D <= 0) {
                // pattern 1
                x++;
                tab[x] = y;
                x++;
                tab[x] = y;
                D += incr1;
            }
            else if (D >= c ) {
                // pattern 3
                x++;
                y++;
                tab[x] = y;
                x++;
                tab[x] = y;
                D +=  incr2;
            }
            else { 
                // pattern 5
                x++;
                tab[x] = y;
                x++;
                y++;
                tab[x] = y;
                x++;
                tab[x] = y;
                D +=  incr3;
            }
        }
    }
    else { //slope >= 1/2 -> non traité ici
    }

    if(x < dx ) {
        tab[x] = y;
    }
}


//////////////////////////////////////////////////////////////////////////

static long gcd (long a, long b) {
    long r, i;
    while(b!=0){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void droite_pgcd( long dx, long dy, long * tab){
    long g = gcd(dx,dy);
    long min_dx = dx/g;
    long min_dy = dy/g;
    size_t size = min_dx * sizeof(long);
    
    droite_3p( min_dx, min_dy, tab);
    
    for( long i = 1; i < g; i++){
        memcpy(tab+(i*min_dx), tab, min_dx * sizeof(long) );
    }

}


//////////////////////////////////////////////////////////////////////////

void line(long u, long v, long longue, long shirt, long * slope){
    long incH= v * 2;
    long incD= incH- u;
    long delta= incD+ v;
    slope[0] = longue;
    slope[u - 1] = shirt;
    long x = 1;
    long cpt = (u - 2) / 4;
    

    for ( ; cpt > 0; cpt--) {  /* (1) */
        if (delta < 0) { /* caseA */
            slope[x] = longue;
            slope[u - ++x]= longue;
            slope[x] = longue;
            slope[u - ++x]= longue;
            delta+= incH;
        }
        else{
            if (delta< v) { /* caseB */
                slope[x] = longue;
                slope[u - ++x] = longue;
                slope[x] = shirt;
                slope[u - ++x]= shirt;
            }
            else{ /* caseC */
                slope[x] = shirt;
                slope[u - ++x] = shirt;
                slope[x] = longue;
                slope[u - ++x]= longue;
            }
            delta+= incD;
        }
    }
    // printf("fin\n");
}

void line2(long u, long v, long longue, long shirt, long * slope){
    long incH= v * 2;
    long incD= incH - u;
    long delta= incD + v;
    // slope[0] = longue;
    // slope[u - 1] = shirt;
    long x = 1;
    long cpt = (u - 2) / 4;

    for ( ; cpt >= 0; cpt--) {  /* (1) */
        if (delta < 0) { /* caseA */
            slope[x] = shirt;
            ++x;
                    
            slope[u - x]= shirt;
            slope[x] = shirt;
            ++x;
                    
            slope[u - x]= shirt;

            
            delta+= incH;
        }
        else{
            if (delta< v) { /* caseB */
                      slope[x] = shirt;
                slope[u - ++x] = shirt;
                     slope[x] = longue;
                slope[u - ++x]= longue;
            }
            else{ /* caseC */
                      slope[x] = longue;
                slope[u - ++x] = longue;
                       slope[x] = shirt;
                  slope[u - ++x]= shirt;
            }
            delta+= incD;
        }
    }
    
}





void droite_pas_auto( long dx, long dy, long * tab){
    long g = gcd(dx,dy);
    long u = dx/g;
    // printf("g : %ld u : %ld ", g, u);
    long v = dy/g;
    long longue = u/v + 1;
    long shirt = longue - 1;
    long nb_l = u % v;
    // printf("longue : %ld \n", longue);
    // printf("shirt %ld \n", shirt);

    if (v > 2*nb_l)
        line2(v, nb_l, longue, shirt, tab);
    else
        line(v, v-nb_l, longue, shirt, tab);
    
    for( long i = 1; i < g; i++){
        // printf("i*v : %ld\n", i*v);
        memcpy(tab+(i*v), tab, v * sizeof(long) );
    }

}

//////////////////////////////////////////////////////////////////////////

void droite_benchmark(char const *fileName ){

    FILE *fp;
    fp = fopen(fileName, "w");


    clock_t t0, t1, dt, t_null;
    t0 = clock();
    t_null = t0 - t0;
    long size_tour_max = 10000;
    

    srand(time(NULL));

    printf("x, Bresenham, pas de deux, pas de trois, pgcd, Span by Span Method\n");
    fprintf(fp,"x,Bresenham, pas de deux, pas de trois, pgcd, Span by Span Method\n");

    for(long dx = 10; dx <= 10000 ; dx*=10){
        long * tab;
        tab = (long *) malloc( (dx * 2) * sizeof(long ) );
        
        long inc = 1;
        long size_sample = dx >> 1;;
        long tour = (size_tour_max / dx);
        long fixTour = 10;
        
        printf("dx : %ld,", dx );
        fprintf(fp,"%ld,", dx );

        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_br(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );
        fprintf(fp,"%*ld,", 0, (long ) dt );

        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_2p(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );
        fprintf(fp,"%*ld,", 0, (long ) dt );


        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_3p(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );
        fprintf(fp,"%*ld,", 0, (long ) dt );


        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_pgcd(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );
        fprintf(fp,"%*ld,", 0, (long ) dt );


        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_pas_auto(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );
        fprintf(fp,"%*ld,", 0, (long ) dt );


        printf("\n" );
        fprintf(fp,"\n" );
    }
}



//////////////////////////////////////////////////////////////////////////
void testAlgo(){

    long * tab;
    tab = (long *) malloc( (22) * sizeof(long ) );
    
    droite_br(20,6,tab);
    affiche(tab,20);
    resetTab( tab, 20 );

    droite_2p(20,6,tab);
    affiche(tab,20);
    resetTab( tab, 20 );

    droite_3p(20,6,tab);
    affiche(tab,20);
    resetTab( tab, 20 );

    droite_pgcd(20,6,tab);
    affiche(tab,20);
    resetTab( tab, 20 );

    // droite_pas_auto(10,6,tab);
    // droite_pas_auto(10,5,tab);
    // affiche2(tab,21);
    // resetTab( tab, 119 );


    free(tab);
    return ;
}

int main(int argc, char const *argv[]) {

    // testAlgo();

    if(argc < 2){
        printf("ERROR - FICHIER MANQUANT\n");
        return 0 ;
    }
    if(argc >= 2){
        //
        droite_benchmark(argv[1]);
    }


    return 0;
}


/*

int main(int argc, char const *argv[]) {
    long * tab;
    tab = (long *) malloc( (20 + 1) * sizeof(long ) );
    
    droite_br(20,6,tab);
    affiche(tab,20);
    resetTab( tab, 20 );

    droite_2p(20,6,tab);
    affiche(tab,20);
    resetTab( tab, 20 );

    droite_3p(20,6,tab);
    affiche(tab,20);
    resetTab( tab, 20 );

    droite_pgcd(20,6,tab);
    affiche(tab,20);
    resetTab( tab, 20 );

    droite_pas_auto(20,6,tab);
    affiche2(tab,20);
    resetTab( tab, 20 );


    free(tab);
    return 0;

    clock_t t0, t1, dt, t_null;
    t0 = clock();
    t_null = t0 - t0;
    long size_sample_max = 100;
    // long * tab;
    
    // tab = (long *) malloc( 2 * sizeof(long ) );

    srand(time(NULL));

    for(long dx = 10; dx < 10000000 ; dx*=10){
        
        tab = (long *) malloc( (dx + 1) * sizeof(long ) );
        
        long inc = 1;
        long size_sample = dx >> 1;
        if(size_sample > size_sample_max){
            inc = size_sample / size_sample_max;
        }

        dt = t_null;
        for( long dy = 0; dy <= size_sample; dy += inc){
            t0 = clock();
            droite_br(dx, dy, tab);
            t1 = clock();
            dt += t1 - t0;
        }
        dt = dt/(size_sample / inc);
        printf( "%*ld,", 10, (long ) dt );
        forceUse(tab, dx);

        dt = t_null;
        for( long dy = 0; dy <= size_sample; dy += inc){
            t0 = clock();
            droite_2p(dx, dy, tab);
            t1 = clock();
            dt += t1 - t0;
        }
        dt = dt/(size_sample / inc);
        printf( "%*ld,", 10, (long ) dt );
        forceUse(tab, dx);

        dt = t_null;
        for( long dy = 0; dy <= size_sample; dy += inc){
            t0 = clock();
            droite_3p(dx, dy, tab);
            t1 = clock();
            dt += t1 - t0;
        }
        dt = dt/(size_sample / inc);
        printf( "%*ld,", 10, (long ) dt );
        forceUse(tab, dx);

        dt = t_null;
        for( long dy = 0; dy <= size_sample; dy += inc){
            t0 = clock();
            droite_pgcd(dx, dy, tab);
            t1 = clock();
            dt += t1 - t0;
        }
        dt = dt/(size_sample / inc);
        printf( "%*ld,", 10, (long ) dt );
        forceUse(tab, dx);



        // printf( "%*ld,", 10, (unsigned long ) inc );
        // printf( "%*ld,", 10, (unsigned long ) size_sample );
        // printf( "%*ld,", 10, (unsigned long ) size_sample / inc  );
        // printf( "%*d,", 10, (int) inc * size_sample_max );


        free(tab);
        printf("\n" );
    }
















    clock_t t0, t1, dt, t_null;
    t0 = clock();
    t_null = t0 - t0;
    long size_tour_max = 10000;
    // long * tab;
    
    // tab = (long *) malloc( 2 * sizeof(long ) );

    srand(time(NULL));

    for(long dx = 10; dx <= 10000 ; dx*=10){
        long * tab;
        tab = (long *) malloc( (dx * 2) * sizeof(long ) );
        
        long inc = 1;
        long size_sample = dx >> 1;;
        long tour = (size_tour_max / dx);
        long fixTour = 10;
        
        printf("dx : %ld", dx );

        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_br(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );

        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_2p(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );

        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_3p(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );

        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_pgcd(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );

        dt = t_null;
        for( long t = 0; t < tour; t ++){          
            for( long f = 0; f < fixTour; f ++){    
                for( long dy = 1; dy <= size_sample; dy ++){
                    t0 = clock();
                    droite_pas_auto(dx, dy, tab);
                    t1 = clock();
                    dt += t1 - t0;
                    forceUse(tab, dx);
                }
            }
        }
        dt = (dt/ size_sample) / tour  ;
        printf( "%*ld,", 10, (long ) dt );

        printf("\n" );
    }




*/