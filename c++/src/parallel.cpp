#include<ctime>
#include<iostream>
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
    int row_start; 
    int row_end; 
    int tops;
    double **Array_of_Distance; 
    int **Array_of_History;
    int thread_cnt;
    sem_t *sem_Array_of_Distance;
};


void Get_The_Shortest_Path_Parallel(int tops, int thread_cnt, double ** Array_of_Distance, int **Array_of_History)
{

    sem_t *sem_Array_of_Distance = (sem_t *)calloc(tops + 1, sizeof(sem_t));

    sem_init(sem_Array_of_Distance, 1, thread_cnt);

    for (int i = 1; i <= tops; i++)sem_init(sem_Array_of_Distance + i, 1, 0);

    if (tops < thread_cnt) thread_cnt = tops;

    pthread_t *threads = (pthread_t *)calloc(thread_cnt, sizeof(pthread_t));

    int thread_last_row = tops % thread_cnt;
    int rows_in_thread = tops / thread_cnt;
    int next_unsigned_row = 0;


    for (int i = 1; i < thread_cnt; i++)
    {
        struct_wa_t *args = (struct_wa_t *)calloc(1, sizeof(struct_wa_t));

        args->Array_of_Distance = Array_of_Distance;
        args->Array_of_History= Array_of_History;
        args->tops = tops;
        args->sem_Array_of_Distance = sem_Array_of_Distance;
        args->thread_cnt = thread_cnt;
        args->row_start = next_unsigned_row;
        args->row_end = next_unsigned_row + rows_in_thread - 1;
            
        if (i <= thread_last_row) args->row_end++;

        next_unsigned_row = args->row_end + 1;

        if (pthread_create(threads + i, NULL, Floyd_Warshall_Coordinator,args) != 0){
            exit;
        }

        if (next_unsigned_row >= tops)break;
    }

    Get_The_Part_Of_Work(next_unsigned_row,
                        next_unsigned_row + rows_in_thread - 1, sem_Array_of_Distance, tops, thread_cnt, Array_of_Distance, Array_of_History);

    for (int i = 0; i < thread_cnt; i++)
    {
        pthread_join(threads[i], NULL);
    }

}


void * Floyd_Warshall_Coordinator(void * data)
{
	struct_wa_t  * args =(struct_wa_t  *)data; 

    Get_The_Part_Of_Work(args->row_start, args->row_end, args->sem_Array_of_Distance, args->tops, args->thread_cnt, args->Array_of_Distance, args->Array_of_History);
    pthread_exit(NULL);
	return NULL;
}


void Get_The_Part_Of_Work(int row_start, int row_end, sem_t *sem_Array_of_Distance, int tops, int thread_cnt, double** Array_Of_Distance, int** Array_Of_History)
{
    for (int k = 0; k < tops; k++)
    {
        sem_wait((sem_Array_of_Distance + k));

        for (int i = row_start; i <= row_end; i++)
        {
            for (int j = 0; j < tops; j++)
            {
                if (Array_Of_Distance[i][k] == INF || Array_Of_Distance[k][j]== INF) continue;

                if (Array_Of_Distance[i][j] > Array_Of_Distance[i][k] + Array_Of_Distance[k][j])
                {
                    Array_Of_Distance[i][j] = Array_Of_Distance[i][k] + Array_Of_Distance[k][j];
                    Array_Of_History[i][j] = Array_Of_History[i][k];
                }
            }

            if (k >= row_start && k <= row_end) 
            {
                for (int f = 0; f < thread_cnt; f++)
                {
                    sem_post(sem_Array_of_Distance + k + 1);
                }
            }
        }
    }
}
