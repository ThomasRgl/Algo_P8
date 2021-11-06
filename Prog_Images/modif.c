/* il s agit de prendre une image et de la modifier */

#include "ima.h"
#include <limits.h>

void gris_uniforme(Image * i) {
  int j, size;
  GLubyte * im, val;
  val = 128;
  size = 3 * i->sizeY * i->sizeX;
  im = i->data;
  for (j = 0; j < size; j ++) {
	*im++ = val;
  }
}
void gris (Image * im) {
  int j, r, g, b, size, moy;
  GLubyte * ptr, val;

  size =  im->sizeY * im->sizeX;
  ptr = im->data;
  for (j = 0; j < size; j ++) {
	r = *ptr++ ;
	g = *ptr++ ;
	b = *ptr ;
	moy = r + g + (int) b;
	moy /= 3;
	val = (GLubyte) moy;
	ptr -= 2;
	*ptr++ = val;
	*ptr++ = val;
	*ptr++ = val;
  }
}
void sobel (Image * im) {
  int i, j, a, b, c, mat [3][3], ma2[3][3], dep [3][3], ligne;
  int moy, limitex, limitey, size;
  GLubyte *ptr, *hor, *horbegin, *ver, *verbegin;
  /* prepa nouvelle matrice */
  size = im->sizeX * im->sizeY * 3;
  horbegin = malloc (size * sizeof(GLubyte));
  assert (horbegin);
  verbegin = malloc (size * sizeof(GLubyte));
  assert (verbegin);

  
  i = 1;
  for (j = 0; j < 3; j++)
    mat[i][j] = 0;
  i = 0;
  for (j = 0; j < 3; j++)
    mat[i][j] = 1;
  mat[i][1] += 1;
  i = 2;
  for (j = 0; j < 3; j++)
    mat[i][j] = -1;
  mat[i][1] -= 1;
  /* filtre Sobel ok */
  ligne = 3 * im->sizeX;
  i = 0;
  for (j = 0; j < 3; j++)
    dep [j][i] = -ligne;
  i = 1;
  for (j = 0; j < 3; j++)
    dep [j][i] = 0;
  i = 2;
  for (j = 0; j < 3; j++)
    dep [j][i] = ligne;
  
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      dep [i][j] += 3 *(i - 1);
  /* normalement les matrices sont bonnes */
  limitey = im->sizeY - 1;
  limitex = im->sizeX - 1;
  hor = horbegin;
  for (i = 1; i < limitey; i++) {
    ptr = im->data + i*ligne;
    for (j = 1; j < limitey; j++) {
      moy = 0;
      for (a = 0; a < 3; a++)
	for (b = 0; b < 3; b++) {
	  for (c = 0; c < 3; c++) {
	    moy += mat[a][b] * *(ptr + c + dep[a][b]);
	  }
	}
      moy /= 8;
      moy += 127;
      if (moy < 0) {
	moy = 0;
	printf(".");
      }
      if (moy > 255) {
	moy = 255;
	printf(",");
      }
      * hor++ = (GLubyte) moy;
    }
  }
  hor = horbegin;
  for (i = 1; i < limitey; i++) {
    ptr = im->data + i*ligne;
    for (j = 1; j < limitey; j++, ptr += 3) {
      *ptr = *hor++;
    }
  }
}
  

void negatif (Image * im){
    int j, r, g, b, size;
    GLubyte * ptr;

    size =  im->sizeY * im->sizeX;
    ptr = im->data;
    for (j = 0; j < size; j ++) {
		r = *ptr++ ;
		g = *ptr++ ;
		b = *ptr ;
		// moy = r + g + (int) b;
		// moy /= 3;
		// val = (GLubyte) moy;
		ptr -= 2;
		*ptr++ = (GLubyte) (255 - (int) r);
		*ptr++ = (GLubyte) (255 - (int) g);
		*ptr++ = (GLubyte) (255 - (int) b);
    }
}

void renverser (Image * im){
    int j, r1, g1, b1, r2, g2, b2, size, sizeMid;
    GLubyte * ptrInc;
	GLubyte * ptrDec;

    size =  im->sizeY * im->sizeX;
    sizeMid = size >> 1;
	
	ptrInc = im->data ;
    ptrDec = ptrInc-1 + size*3; 

	for (j = 0 ; j < sizeMid; j ++) {
		
		r1 = *ptrInc++ ;
		g1 = *ptrInc++ ;
		b1 = *ptrInc ;

		b2 = *ptrDec-- ;
		g2 = *ptrDec-- ;
		r2 = *ptrDec ;

		ptrInc -= 2;
		ptrDec += 2;

		*ptrInc++ = (GLubyte)  r2;
		*ptrInc++ = (GLubyte)  g2;
		*ptrInc++ = (GLubyte)  b2;

		*ptrDec-- = (GLubyte)  b1;
		*ptrDec-- = (GLubyte)  g1;
		*ptrDec-- = (GLubyte)  r1;
    }


}

void addGreen(Image * im){
    int j, g, size;
    GLubyte * ptr;

    size =  im->sizeY * im->sizeX;
    ptr = im->data;
  	ptr++;
    for (j = 0; j < size; j ++) {
		
		g = *ptr;
		
		g += 10;
		if(g > 255)
			g=255;

		*ptr = (GLubyte) g;
		
		ptr+=3 ;
		
    }
}