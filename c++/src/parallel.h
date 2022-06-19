#include<semaphore.h>
void Get_The_Shortest_Path_Parallel(int tops, int thread_count, double ** Adjacency_Array, int **Array_of_History);
void * floyd_warshall_worker( void * args);
void floyd_warshall_fractional(int starting_row, int ending_row, sem_t *sem_Adjacency_Array, int tops, int thread_count, double** Array_Of_Distance, int** Array_Of_History);
