#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "papi.h"

#include "gemm.h"

static int verify_command_line (int argc, char *argv[], int *m_size, int *version);
static int alloc_matrix (float **m, int m_size);
static int ini_zero_matrix (float **m, int N);
static int ini_matrix (float **m, int m_size);
static int free_matrix (float **m);
static void print_usage (char *msg);
static float my_rand (void);

void (*func)(float *, float *, float *, int);

// PAPI events to monitor
#define NUM_EVENTS 3
int Events[NUM_EVENTS] = { PAPI_TOT_CYC, PAPI_TOT_INS , PAPI_L1_TCA };
// PAPI counters' values
long long values[NUM_EVENTS], min_values[NUM_EVENTS];
int retval, EventSet=PAPI_NULL;

// number of times the function is executed and measured
#define NUM_RUNS 5

int main (int argc, char *argv[]) {
    long long start_usec, end_usec, elapsed_usec, min_usec=0L;
    int m_size, total_elements, version, i, run;
    float *a, *b, *c;
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
    fprintf (stdout, "Initializing Matrix A...");
    if (!ini_matrix (&a, total_elements)) return 0;
    fprintf (stdout, "done!\n");
    
    // ini B matrix
    fprintf (stdout, "Initializing Matrix B...");
    if (!ini_matrix (&b, total_elements)) return 0;
    fprintf (stdout, "done!\n");
    
    // alloc C matrix
    fprintf (stdout, "Initializing Matrix C...");
    if (!ini_zero_matrix (&c, total_elements)) return 0;
    fprintf (stdout, "done!\n");
    
    
    // warmup caches
    fprintf (stdout, "Warming up caches...");
    func (a, b, c, m_size);
    fprintf (stdout, "done!\n");
    
    for (run=0 ; run < NUM_RUNS ; run++) {
        fprintf (stderr, "\nrun=%d - Computing C = A * B...", run);
        
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
        fprintf (stderr, "done!\n");
        
        elapsed_usec = end_usec - start_usec;
        
        if ((run==0) || (elapsed_usec < min_usec)) {
            min_usec = elapsed_usec;
            for (i=0 ; i< NUM_EVENTS ; i++) min_values[i] = values [i];
        }
        
    } // end runs
    printf ("\nWall clock time: %lld usecs\n", min_usec);
    
    // output PAPI counters' values
    for (i=0 ; i< NUM_EVENTS ; i++) {
        char EventCodeStr[PAPI_MAX_STR_LEN];
        
        if (PAPI_event_code_to_name(Events[i], EventCodeStr) == PAPI_OK) {
            fprintf (stdout, "%s = %lld\n", EventCodeStr, min_values[i]);
        } else {
            fprintf (stdout, "PAPI UNKNOWN EVENT = %lld\n", min_values[i]);
        }
    }
    
    // evaluate CPI and Texec here
    
    free_matrix (&a);
    free_matrix (&b);
    free_matrix (&c);
    
    printf ("\nThat's all, folks\n");
    return 1;
}

int verify_command_line (int argc, char *argv[], int *total_elements, int *version) {
    int val;
    
    if (argc!=3) {
        print_usage ((char *)"Exactly 2 arguments are required!");
        return 0;
    }
    
    val = atoi (argv[1]);
    
    if (val <= 0) {
        print_usage ((char *)"The matrix size is the number of rows of a square matrix and must be a positive integer!");
        return 0;
    }
    else {
        *total_elements = val;
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

int alloc_matrix (float **m, int N) {
    
    *m = (float *) malloc (N*sizeof(float));
    if (!(*m)) {
        print_usage ((char *)"Could not allocate memory for matrix!");
        return 0;
    }
    return 1;
}

float my_rand (void) {
    double d;
    
    d = drand48 ();
    d *= 1.E10;
    d -= 0.5E10;
    return ((float)d);
}

int ini_matrix (float **m, int N) {
    int i;
    float *ptr;
    
    if (!alloc_matrix (m, N)) return 0;
    for (i=0 , ptr = (*m) ; i<N ; i++ , ptr++) {
        *ptr = my_rand();
    }
    return 1;
} 

int ini_zero_matrix (float **m, int N) {
    if (!alloc_matrix (m, N)) return 0;
    bzero ((*m), N*sizeof(float));
    return 1;
} 

int free_matrix (float **m) {
    free (*m);
    *m = NULL;
    return 1;
}



