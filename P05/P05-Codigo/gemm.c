#include <stdio.h>

#include "gemm.h"

/*
 * gemm1
 * Algoritmo não optimizado
 */

void gemm1  (float *a, float *b, float *c, int n) {
	int i, j, k;

	for (j = 0; j < n; ++j) {
		for(k = 0; k < n; k++ ) {
			for (i = 0; i < n; ++i) {
				/* c[i][j] += a[i][k]*b[k][j] */
				c[i*n+j] += a[i*n+k] * b[k*n+j]; 
			}
		}
	}
}


/*
 * gemm2
 * Algoritmo : loops reordered for increased spatial locality
 */

void gemm2  (float *a, float *b, float *c, int n) {
	int i, j, k;

	for (i = 0; i < n; ++i) {
		for(k = 0; k < n; k++ ) {
			for (j = 0; j < n; ++j) {
				/* c[i][j] += a[i][k]*b[k][j] */
				c[i*n+j] += a[i*n+k] * b[k*n+j]; 
			}
		}
	}
}


/*
 * gemm3
 * Algoritmo : Using a local for aik
 */

void gemm3  (float *a, float *b, float *c, int n) {
	int i, j, k;
	float aik;

	for (i = 0; i < n; ++i) {
		for(k = 0; k < n; k++ ) {
			aik = a[i*n+k];
			for (j = 0; j < n; ++j) {
				/* c[i][j] += a[i][k]*b[k][j] */
				c[i*n+j] += aik * b[k*n+j]; 
			}
		}
	}
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
 * Algoritmo Auto-vectorization
 */

#pragma GCC target("arch=znver2")
#pragma GCC optimize("tree-vectorize")

//#ifndef __SSE3__
//#error This example requires SSE3
//#endif

void gemm6  (float * __restrict__ a, float * __restrict__ b, float * __restrict__ c, int n) {
	int i, j, k;
	float aik;

	for (i = 0; i < n; ++i) {
		for(k = 0; k < n; k++ ) {
			aik = a[i*n+k];
			for (j = 0; j < n; ++j) {
				/* c[i][j] += a[i][k]*b[k][j] */
				c[i*n+j]  += aik * b[k*n+j]; 
			}
		}
	}
}


/*
 * gemm7
 * Algoritmo
 */

void gemm7  (float * __restrict__ a, float * __restrict__ b, float * __restrict__ c, int n) {
	int i, j, k;
	float cij;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			cij = c[i*n+j]; /* cij = C[i][j] */
			for(k = 0; k < n; k++ ) {
				cij += a[i*n+k]*b[j*n+k]; /* cij += A[i][k]*B[j][k] */
			}
			c[i*n+j] = cij;
		}
	}

}

/*
 * gemm8
 * Algoritmo 
 */

void gemm8  (float *a, float *b, float *c, int n) {
  //fprintf (stderr, "gemm8() not supported!\n\n");
  return ;
}

/*
 * gemm9
 * Algoritmo 
 */

void gemm9  (float *a, float *b, float *c, int n) {
  //fprintf (stderr, "gemm9() not supported!\n\n");
  return ;
}

/*
 * gemm10
 * Algoritmo 
 */

void gemm10  (float *a, float *b, float *c, int n) {
  //fprintf (stderr, "gemm10() not supported!\n\n");
  return ;
}



