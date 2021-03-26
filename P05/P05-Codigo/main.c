#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "papi.h"

#include "gemm.h"

static float a[M_SIZE*M_SIZE] __attribute__((aligned (16)));
static float b[M_SIZE*M_SIZE] __attribute__((aligned (16)));
static float c[M_SIZE*M_SIZE] __attribute__((aligned (16)));
static float ref[M_SIZE*M_SIZE] __attribute__((aligned (16)));

static int ini_matrices (int );
static float my_rand (void);

static int verify_command_line (int argc, char *argv[], int *m_size, int *version);
static void print_usage (char *msg);
static int verify_result(int);
static void gemm_ref  (int );
static void print_Matrices (int);

void (*func)(float *, float *,float *, int);

// PAPI events to monitor
#define NUM_EVENTS 2
int Events[NUM_EVENTS] = { PAPI_TOT_CYC, PAPI_TOT_INS };
// PAPI counters' values
long long values[NUM_EVENTS], min_values[NUM_EVENTS];
int retval, EventSet=PAPI_NULL;

// number of times the function is executed and measured
#define NUM_RUNS 3

int main (int argc, char *argv[]) {
  long long start_usec, end_usec, elapsed_usec, min_usec=0L;
  int m_size, total_elements, version, i, run;
  int num_hwcntrs = 0;

  if (!verify_command_line (argc, argv, &m_size, &version)) {
	return 0;
  }
  total_elements = m_size * m_size;

  fprintf (stdout, "Square matrices have %d rows for a total of %d elements!\n", m_size, total_elements);

  fprintf (stdout, "\nSetting up PAPI...");
  // Initialize PAPI
  retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT) {
    fprintf(stderr,"PAPI library init error!\n");
    return 0;
  }

  /* create event set */
  if (PAPI_create_eventset(&EventSet) != PAPI_OK) {
    fprintf(stderr,"PAPI create event set error\n");
    return 0;
  }
    
    /* Get the number of hardware counters available */
    if ((num_hwcntrs = PAPI_num_hwctrs()) <= PAPI_OK)  {
        fprintf (stderr, "PAPI error getting number of available hardware counters!\n");
        return 0;
    }
    fprintf(stdout, "done!\nThis system has %d available counters.\n\n", num_hwcntrs);
    

  // We will be using at most NUM_EVENTS counters
  if (num_hwcntrs >= NUM_EVENTS) {
    num_hwcntrs = NUM_EVENTS;
  } else {
    fprintf (stderr, "Error: there aren't enough counters to monitor %d events!\n", NUM_EVENTS);
    return 0;
  }
    
    if (PAPI_add_events(EventSet,Events,NUM_EVENTS) != PAPI_OK)  {
        fprintf(stderr,"PAPI library add events error!\n");
        return 0;
    }

  // ini A matrix
  fprintf (stdout, "Initializing matrices...");
  if (!ini_matrices (m_size)) return 0;
  fprintf (stdout, "done!\n");

  fprintf (stdout, "Code version %d: %s\n", version, Version_desc[version-1]);

  // warmup caches
  fprintf (stdout, "Warming up caches...");
  // set C to zero
  bzero (c, total_elements*sizeof(float));
  func (a, b, c, m_size);
  fprintf (stdout, "done!\n");

  for (run=0 ; run < NUM_RUNS ; run++) { 

   fprintf (stderr, "run=%d ...", run);

   // set C to zero
   bzero (c, total_elements*sizeof(float));
   // use PAPI timer (usecs) - note that this is wall clock time
   // for process time running in user mode -> PAPI_get_virt_usec()
   // real and virtual clock cycles can also be read using the equivalent
   // PAPI_get[real|virt]_cyc()
   start_usec = PAPI_get_real_usec();

   /* Start counting events */
      if (PAPI_start(EventSet) != PAPI_OK) {
          fprintf (stderr, "PAPI error starting counters!\n");
          return 0;
      }

   func (a, b, c, m_size);

   /* Stop counting events */
      if (PAPI_stop(EventSet,values) != PAPI_OK) {
          fprintf (stderr, "PAPI error stoping counters!\n");
          return 0;
      }

   end_usec = PAPI_get_real_usec();
   fprintf (stderr, "done!\t");

   elapsed_usec = end_usec - start_usec;

   if ((run==0) || (elapsed_usec < min_usec)) {
      min_usec = elapsed_usec;
      for (i=0 ; i< NUM_EVENTS ; i++) min_values[i] = values [i];
   }

  } // end runs
  printf ("\n\nWall clock time: %lld usecs\n", min_usec);
  
  // output PAPI counters' values
  for (i=0 ; i< NUM_EVENTS ; i++) {
	  char EventCodeStr[PAPI_MAX_STR_LEN];

	  if (PAPI_event_code_to_name(Events[i], EventCodeStr) == PAPI_OK) {
		fprintf (stdout, "%s = %lld\n", EventCodeStr, min_values[i]);
	  } else {
		fprintf (stdout, "PAPI UNKNOWN EVENT = %lld\n", min_values[i]);
	  }
  }

#if NUM_EVENTS >1
  // evaluate CPI and Texec here
  if ((Events[0] == PAPI_TOT_CYC) && (Events[1] == PAPI_TOT_INS)) {
    float CPI = ((float) min_values[0]) / ((float) min_values[1]);
    float CPE = ((float) min_values[0]) / ((float) total_elements);
    long long Texec = (long long) (((float)min_values[0])/2e3);
    fprintf (stdout, "CPI = %.2f; CPE = %.0f\nEstimated Texec = %lld\n", CPI, CPE, Texec);
  }
#endif

  // verify the results
  // generate reference
  fprintf (stdout, "generating the reference solution...");
  gemm_ref (m_size);
  fprintf (stdout, "done!\n");

  //print_Matrices (m_size);

  // generate reference
  fprintf (stdout, "comparing reference solution with C...");
  if (verify_result (m_size)) {
	fprintf (stdout, "  OK!\n");
  }
  else {
  	fprintf (stdout, "  ERROR!\n");
  }
  

  printf ("\nThat's all, folks\n");
  return 1;
}

int verify_command_line (int argc, char *argv[], int *m_size, int *version) {
	int val;

	if (argc!=3) {
		print_usage ((char *)"Exactly 2 arguments are required!");
		return 0;
	}

	val = atoi (argv[1]);

	if (val <= 0) {
		char s[150];
		sprintf (s, "The matrix size is the number of rows of a square matrix and must be a positive integer less or equal than %d!", M_SIZE);
		print_usage (s);
		return 0;
	}
	else {
		*m_size = val;
	}
		
	val = atoi (argv[2]);

	if ((val <= 0) || (val >10)) {
		print_usage ((char *)"The version of the gemm matrix to use must be an integer between 1 and 10!");
		return 0;
	}
	else {
		*version = val;
		switch (*version) {
			case 1:
				func = &gemm1;
				break;
			case 2:
				func = &gemm2;
				break;
			case 3:
				func = &gemm3;
				break;
			case 4:
				func = &gemm4;
				break;
			case 5:
				func = &gemm5;
				break;
			case 6:
				func = &gemm6;
				break;
			case 7:
				func = &gemm7;
				break;
			case 8:
				func = &gemm8;
				break;
			case 9:
				func = &gemm9;
				break;
			case 10:
				func = &gemm10;
				break;
		}
	}
		
	return 1;
}

void print_usage (char *msg) {
	fprintf (stderr, "Command Line Error! %s\n", msg);
	fprintf (stderr, "Usage:\tgemm <matrix size> <version>\n\n");
}


//----------------------------------------------

//Initialization funcs...

static float my_rand (void) {
  double d;

  d = drand48 ();
  d *= 4.E0;
  return ((float)d);
}

static int ini_matrices (int N) {
 	int i;
	float *ptr;

	const int total_elements = N*N;
	for (i=0 , ptr = a ; i<total_elements ; i++ , ptr++) {
		*ptr = my_rand();
	}
	for (i=0 , ptr = b ; i<total_elements ; i++ , ptr++) {
		*ptr = my_rand();
	}
	bzero (c, total_elements*sizeof(float));
	bzero (ref, total_elements*sizeof(float));
	return 1;
} 

// -------------------------------------------------------

//Result verification functions

/**
 * Function used to verify the result. No need to change this one.
 */
static int verify_result(int n) {
        float e_sum;
        int i, j, ndx;

        e_sum = 0.f;
        for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
			ndx = i*n+j;
                        e_sum += (c[ndx] < ref[ndx] ?
                                ref[ndx] - c[ndx] :
                                c[ndx] - ref[ndx]);
                }
        }

        printf("e_sum: %f", e_sum);

        return (e_sum < 1E-6);
}

static void gemm_ref  (int n) {
	int i, j, k;
	float aik;

	for (i = 0; i < n; ++i) {
		for(k = 0; k < n; k++ ) {
			aik = a[i*n+k];
			for (j = 0; j < n; ++j) {
				ref[i*n+j] += aik * b[k*n+j]; 
			}
		}
	}
}

static void print_Matrices (int n) {
  int i,j;

  for (i=0 ; i<n ; i++) {
    for (j=0 ; j<n ; j++) {
      printf ("a[%d][%d] = %.2e\t", i, j, a[i*n+j]);
    }
    printf ("\n");
  }
  printf ("\n");
  for (i=0 ; i<n ; i++) {
    for (j=0 ; j<n ; j++) {
      printf ("b[%d][%d] = %.2e\t", i, j, b[i*n+j]);
    }
    printf ("\n");
  }
  printf ("\n");
  for (i=0 ; i<n ; i++) {
    for (j=0 ; j<n ; j++) {
      printf ("c[%d][%d] = %.2e\t", i, j, c[i*n+j]);
    }
    printf ("\n");
  }
  printf ("\n");
  for (i=0 ; i<n ; i++) {
    for (j=0 ; j<n ; j++) {
      printf ("r[%d][%d] = %.2e\t", i, j, ref[i*n+j]);
    }
    printf ("\n");
  }
  printf ("\n");
}
