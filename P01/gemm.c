#include <stdio.h>
#include "gemm.h"

/*
 * gemm1
 * Algoritmo não optimizado
 */

void gemm1  (float *a, float *b, float *c, int n) {
	int i, j, k;
	float cij;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			cij = c[i*n+j]; /* cij = C[i][j] */
			for(k = 0; k < n; k++ ) {
                		cij += a[i*n+k]*b[k*n+j]; /* cij += A[i][k]*B[k][j] */
			}
            		c[i*n+j]=cij; /* C[i][j] = cij */
		}
	}
}


/*
 * gemm2
 * Algoritmo 
 */

void gemm2  (float *a, float *b, float *c, int n) {
  int i, j, k;
	float cij;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			cij = c[i*n+j]; /* cij = C[i][j] */
			for(k = 0; k < n; k++ ) {
                		cij += a[i*n+k]*b[j*n+k]; /* cij += A[i][k]*B[j][k] */
			}
            		c[i*n+j]=cij; /* C[i][j] = cij */
		}
	}
}

/*
 * gemm3
 * Algoritmo 
 */

void gemm3  (float *a, float *b, float *c, int n) {
  fprintf (stderr, "gemm3() not supported!\n\n");
  return ;
}

/*
 * gemm4
 * Algoritmo 
 */

void gemm4  (float *a, float *b, float *c, int n) {
  fprintf (stderr, "gemm4() not supported!\n\n");
  return ;
}

/*
 * gemm5
 * Algoritmo 
 */

void gemm5  (float *a, float *b, float *c, int n) {
  fprintf (stderr, "gemm5() not supported!\n\n");
  return ;
}

/*
 * gemm6
 * Algoritmo 
 */

void gemm6  (float *a, float *b, float *c, int n) {
  fprintf (stderr, "gemm6() not supported!\n\n");
  return ;
}

/*
 * gemm7
 * Algoritmo 
 */

void gemm7  (float *a, float *b, float *c, int n) {
  fprintf (stderr, "gemm7() not supported!\n\n");
  return ;
}

/*
 * gemm8
 * Algoritmo 
 */

void gemm8  (float *a, float *b, float *c, int n) {
  fprintf (stderr, "gemm8() not supported!\n\n");
  return ;
}

/*
 * gemm9
 * Algoritmo 
 */

void gemm9  (float *a, float *b, float *c, int n) {
  fprintf (stderr, "gemm9() not supported!\n\n");
  return ;
}

/*
 * gemm10
 * Algoritmo 
 */

void gemm10  (float *a, float *b, float *c, int n) {
  fprintf (stderr, "gemm10() not supported!\n\n");
  return ;
}
