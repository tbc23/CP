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
				cij += a[i*n+k] * b[k*n+j]; /* cij += A[i][k]*B[k][j] */
			}
			c[i*n+j] = cij; /* C[i][j] = cij */
		}
	}
}


/*
 * gemm2
 * Algoritmo B transposed
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
 * Algoritmo blocked and B transposed
 */

#define BLOCKSIZE 8

void gemm3 (float *a, float *b, float *c, int n) {
  int sj, si, sk;
  int i, j, k;
  float cij;

  for (si = 0; si < n; si += BLOCKSIZE ) {
    for (sj = 0; sj < n; sj += BLOCKSIZE ) {
      for (sk = 0; sk < n; sk += BLOCKSIZE ) {
        // DO BLOCK
        for (i = si; i < si+BLOCKSIZE; ++i) {
          for (j = sj; j < sj+BLOCKSIZE; ++j) {

            cij = c[i*n+j];/* cij = C[i][j] */
            for( k = sk; k < sk+BLOCKSIZE; k++ ) {
              cij += a[i*n+k] * b[k*n+j];/* cij+=A[i][k]*B[k][j] */
            }
            c[i*n+j] = cij;/* C[i][j] = cij */
          }
        }
        // END DO BLOCK
      }
    }
  }
}


/*
 * gemm4
 * Algoritmo 
 */

void gemm4  (float *a, float *b, float *c, int n) {
  int sj, si, sk;
  int i, j, k;
  float cij;

  for (si = 0; si < n; si += BLOCKSIZE ) {
    for (sj = 0; sj < n; sj += BLOCKSIZE ) {
      for (sk = 0; sk < n; sk += BLOCKSIZE ) {
        // DO BLOCK
        for (i = si; i < si+BLOCKSIZE; ++i) {
          for (j = sj; j < sj+BLOCKSIZE; ++j) {

            cij = c[i*n+j];/* cij = C[i][j] */
            for( k = sk; k < sk+BLOCKSIZE; k+=2 ) {
              cij += a[i*n+k] * b[k*n+j];/* cij+=A[i][k]*B[k][j] */
              cij += a[i*n+(k+1)] * b[(k+1)*n+j];
            }
            c[i*n+j] = cij;/* C[i][j] = cij */
          }
        }
        // END DO BLOCK
      }
    }
  }
}

/*
 * gemm5
 * Algoritmo 
 */

void gemm5  (float *a, float *b, float *c, int n) {
  int sj, si, sk;
  int i, j, k;
  float cij, cij2;

  for (si = 0; si < n; si += BLOCKSIZE ) {
    for (sj = 0; sj < n; sj += BLOCKSIZE ) {
      for (sk = 0; sk < n; sk += BLOCKSIZE ) {
        // DO BLOCK
        for (i = si; i < si+BLOCKSIZE; ++i) {
          for (j = sj; j < sj+BLOCKSIZE; j+=2) {

            cij = c[i*n+j];/* cij = C[i][j] */
            cij2 = c[i*n+j+1];
            for( k = sk; k < sk+BLOCKSIZE; k+=2 ) {
              cij += a[i*n+k] * b[k*n+j];/* cij+=A[i][k]*B[k][j] */
              cij += a[i*n+(k+1)] * b[(k+1)*n+j];
            }
            c[i*n+j] = cij;/* C[i][j] = cij */
            c[i*n+j+1] = cij2;
          }
        }
        // END DO BLOCK
      }
    }
  }
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
