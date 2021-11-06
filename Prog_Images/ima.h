#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

#define __OSX__
#ifndef __OSX__
/* pour Bocal */
#include <GL/glut.h>      
#else
/* pour mac */
#include <GL/glut.h>
#endif


struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;
typedef unsigned short utab [3][3][3];

int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);
void upsidedown(Image *);
void gris_uniforme (Image *);
void gris (Image *);
void negatif (Image *);
void renverser(Image *);
void addGreen(Image * );
void sobel (Image *);

