#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h> 
#include <pthread.h>
#include <iostream>
using namespace std;
#define INF 1e9


struct worker_args
{
    int starting_row; // The first row to compute on for a thread
    int ending_row; // The last row to compute on for a thread
    int vertex_count; // How many vertices are in the graph (size of Adjacency_Array)
    double **dist_Adjacency_Array; // Pointer to dist_Adjacency_Array to compute upon
    double **dist_Array_of_History;
    int thread_count; // How many threads are working in parallel
    sem_t *sem_Adjacency_Array; // Adjacency_Array of semaphores to sync threads
};
typedef struct worker_args worker_args_t;


int floyd_warshall_fractional(int starting_row, int ending_row, int vertex_count, double **dist_Adjacency_Array, double ** dist_Array_of_History, int thread_count, sem_t *sem_Adjacency_Array)
{
    for (int k = 0; k < vertex_count; k++)
    {
        sem_wait((sem_Adjacency_Array + k));

        // Only execute for assigned rows
        for (int i = starting_row; i <= ending_row; i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                if (dist_Adjacency_Array [i][k] == INF ||
                    dist_Adjacency_Array[k][j] == INF)
                {
                    cout<<"Is INF"<<endl;
                    continue;
                }
                // this part is the same as before
                if (dist_Adjacency_Array[i][j] > dist_Adjacency_Array[i][k] + dist_Adjacency_Array[k][j])
                {
                    cout<<"change pos"<<endl;
                    dist_Adjacency_Array[i][j] = dist_Adjacency_Array[i][k] + dist_Adjacency_Array[k][j];
                    dist_Array_of_History[i][j] = dist_Array_of_History[i][k];

                }
            }
            // Every time we finish one of our own rows,
            // (when it is equal to k) 
            // we need to update the semaphore values
            if (k >= starting_row && k <= ending_row) 
            {
                for (int z = 0; z < thread_count; z++)
                {
                    // the + 1 is an offset, so that for iteration 0 we
                    // still check a semaphore (for simplicity of loop)
                    sem_post(sem_Adjacency_Array + k + 1);
                }
            }
        }
    }
    
    return 0;
}


void *floyd_warshall_worker(void *args)
{
    struct worker_args * wa = (struct worker_args *)args; 

    floyd_warshall_fractional(wa->starting_row, wa->ending_row, wa->vertex_count,
                          wa->dist_Adjacency_Array, wa->thread_count, wa->sem_Adjacency_Array);
    pthread_exit(NULL);
    return NULL;
}

int floyd_warshall_parallel( double ** Adjacency_Array, int vertex_count, int thread_count)
{
    // the + 1 is an offset, so that for iteration 0 we
    // still check a semaphore (for simplicity of loop)
    sem_t *sem_Adjacency_Array =
                (sem_t *)calloc(vertex_count + 1, sizeof(sem_t));
    // create a semaphore for each row (one for each k value)
    // make one extra one due to the nature of the loop
    sem_init(sem_Adjacency_Array, 1, thread_count); // first semaphore should already be unlocked

    for (int i = 1; i <= vertex_count; i++)
    {
        // subsequent ones need to wait.
        sem_init(sem_Adjacency_Array + i, 1, 0);
    }
    if (vertex_count < thread_count)
    {
        thread_count = vertex_count;
    }

    pthread_t *threads = (pthread_t *)calloc(thread_count, sizeof(pthread_t));
    int rows_per_thread = vertex_count / thread_count;
    int threads_with_extra_row = vertex_count % thread_count;
    int next_unassigned_row = 0;


    for (int i = 1; i < thread_count; i++)
    {
        worker_args_t *wa = (worker_args_t *)calloc(1, sizeof(worker_args_t));
        wa->dist_Adjacency_Array = Adjacency_Array;
        wa->sem_Adjacency_Array = sem_Adjacency_Array;
        wa->vertex_count = vertex_count;
        wa->starting_row = next_unassigned_row;
        // subtract 1 so that if you only have 1 row per thread,
        // both start and end are the same number
        wa->ending_row = next_unassigned_row + rows_per_thread - 1;
        wa->thread_count = thread_count;
        // determine if we will have one extra row this thread
        if (i <= threads_with_extra_row) 
        {
            wa->ending_row++;
        }
        next_unassigned_row = wa->ending_row + 1;

        if (pthread_create(threads + i, NULL, floyd_warshall_worker, wa) != 0){
                    printf("floyd_warshall_parallel: error, could not"
                        " create a worker thread");
        }
        {
            cout<<"I am in a parallel" <<endl;
        }

        if (next_unassigned_row >= vertex_count)
        {

            break;
        }
    }
    cout<<"\n"<<next_unassigned_row<<"\n";

    // Execute this thread's portion of the work
    floyd_warshall_fractional(next_unassigned_row,
                        next_unassigned_row + rows_per_thread - 1, vertex_count, 
                            Adjacency_Array, thread_count, sem_Adjacency_Array);

    // Rejoin other threads
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}