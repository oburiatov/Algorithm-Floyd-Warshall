#include <semaphore.h> 
int floyd_warshall_parallel(double **Adjacency_Array, int vertex_count,  int thread_count);
void *floyd_warshall_worker(void *args);
int floyd_warshall_fractional(int starting_row, int ending_row, int vertex_count, double **dist_Adjacency_Array,double **dist_Array_of_History, int thread_count, sem_t *sem_Adjacency_Array);
