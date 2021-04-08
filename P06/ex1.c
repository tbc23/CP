#include<omp.h>
#include<stdio.h>

int main() {
	#pragma omp parallel num_threads(2) 
	//#pragma omp for
	//#pragma omp for ordered
	//#pragma omp for schedule(static,10)
	//#pragma omp for schedule(dynamic,10)
	#pragma omp for schedule(guided)
	//#pragma omp master
	//#pragma omp single
	//#pragma omp critical
	for(int i=0;i<500;i++) {
		int id = omp_get_thread_num();
		//#pragma omp ordered
		printf("T%d:i%d ", id, i);
		//#pragma omp barrier
	} 
}