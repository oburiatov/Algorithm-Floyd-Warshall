#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include"parallel.h"

using namespace std;
#define INF 1e9
typedef struct struct_wa struct_wa_t;

struct struct_wa
{
    int starting_row; 
    int ending_row; 
    int tops;
    double **Array_of_Distance; 
    int **Array_of_History;
    int thread_count;
    sem_t *sem_Array_of_Distance;
};


void Get_The_Shortest_Path_Parallel(int tops, int thread_count, double ** Array_of_Distance, int **Array_of_History)
{

    sem_t *sem_Array_of_Distance = (sem_t *)calloc(tops + 1, sizeof(sem_t));
    sem_init(sem_Array_of_Distance, 1, thread_count);

    for (int i = 1; i <= tops; i++)sem_init(sem_Array_of_Distance + i, 1, 0);

    if (tops < thread_count) thread_count = tops;

    pthread_t *threads = (pthread_t *)calloc(thread_count, sizeof(pthread_t));

    int thread_last_row = tops % thread_count;
    int rows_per_thread = tops / thread_count;
    int next_unassigned_row = 0;


    for (int i = 1; i < thread_count; i++)
    {
        struct_wa_t *wa = (struct_wa_t *)calloc(1, sizeof(struct_wa_t));

        wa->Array_of_Distance = Array_of_Distance;
        wa->Array_of_History= Array_of_History;
        wa->tops = tops;
        wa->sem_Array_of_Distance = sem_Array_of_Distance;
        wa->thread_count = thread_count;
        wa->starting_row = next_unassigned_row;
        wa->ending_row = next_unassigned_row + rows_per_thread - 1;
            
        if (i <= thread_last_row) wa->ending_row++;

        next_unassigned_row = wa->ending_row + 1;

        if (pthread_create(threads + i, NULL, Floyd_Warshall_Coordinator,wa) != 0){
                    printf("floyd_warshall_parallel: error, could not"
                        " create a worker thread");
        }

        if (next_unassigned_row >= tops)break;
    }

    Get_The_Part_Of_Work(next_unassigned_row,
                        next_unassigned_row + rows_per_thread - 1, sem_Array_of_Distance, tops, thread_count, Array_of_Distance, Array_of_History);

    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

}


void * Floyd_Warshall_Coordinator(void * args)
{
	struct_wa_t  * wa =(struct_wa_t  *)args; 

    Get_The_Part_Of_Work(wa->starting_row, wa->ending_row, wa->sem_Array_of_Distance, wa->tops, wa->thread_count, wa->Array_of_Distance, wa->Array_of_History);
    pthread_exit(NULL);
	return NULL;
}


void Get_The_Part_Of_Work(int starting_row, int ending_row, sem_t *sem_Array_of_Distance, int tops, int thread_count, double** Array_Of_Distance, int** Array_Of_History)
{
    for (int k = 0; k < tops; k++)
    {
        sem_wait((sem_Array_of_Distance + k));

        for (int i = starting_row; i <= ending_row; i++)
        {
            for (int j = 0; j < tops; j++)
            {
                if (Array_Of_Distance[i][k] == INF || Array_Of_Distance[k][j]== INF)
                {
                    continue;
                }
                if (Array_Of_Distance[i][j] > Array_Of_Distance[i][k] + Array_Of_Distance[k][j])
                {
                    Array_Of_Distance[i][j] = Array_Of_Distance[i][k] + Array_Of_Distance[k][j];
                    Array_Of_History[i][j] = Array_Of_History[i][k];
                }
            }

            if (k >= starting_row && k <= ending_row) 
            {
                for (int z = 0; z < thread_count; z++)
                {
                    sem_post(sem_Array_of_Distance + k + 1);
                }
            }
        }
    }
}
