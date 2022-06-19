#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include"parallel.h"

using namespace std;
#define INF 1e9
typedef struct worker_args worker_args_t;

struct worker_args
{
    int starting_row; 
    int ending_row; 
    int vertex_count;
    double **dist_Array_of_Distance; 
    int **dist_Array_of_History;
    int thread_count;
    sem_t *sem_Array_of_Distance;
};


void Get_The_Shortest_Path_Parallel(int tops, int thread_count, double ** Array_of_Distance, int **Array_of_History)
{

    sem_t *sem_Array_of_Distance = (sem_t *)calloc(tops + 1, sizeof(sem_t));
    sem_init(sem_Array_of_Distance, 1, thread_count);

    for (int i = 1; i <= tops; i++)
    {
        sem_init(sem_Array_of_Distance + i, 1, 0);
    }
    if (tops < thread_count)
    {
        thread_count = tops;
    }

    pthread_t *threads = (pthread_t *)calloc(thread_count, sizeof(pthread_t));
    int rows_per_thread = tops / thread_count;
    int threads_with_extra_row = tops % thread_count;
    int next_unassigned_row = 0;

    worker_args_t *wa = (worker_args_t *)calloc(1, sizeof(worker_args_t));    
    wa->dist_Array_of_Distance = Array_of_Distance;
    wa->dist_Array_of_History= Array_of_History;
    cout<<"Array Of Distance"<<endl;
    // for (int i = 0; i < tops; i++)
    // {
    //     for (int j = 0; j < tops; j++)
    //     {
    //         cout<< Array_of_Distance[i][j]<<"\t";
    //     }
    //     cout<<endl;
        
    // }
    
    wa->vertex_count = tops;
    wa->sem_Array_of_Distance = sem_Array_of_Distance;
    wa->thread_count = thread_count;


    for (int i = 1; i < thread_count; i++)
    {

        
        
        wa->starting_row = next_unassigned_row;
        wa->ending_row = next_unassigned_row + rows_per_thread - 1;
        if (i <= threads_with_extra_row) 
        {
            wa->ending_row++;
        }

        next_unassigned_row = wa->ending_row + 1;
		cout<<"!!!!!!!!starting "<< wa->starting_row<< " "<<wa->ending_row<<endl;
        if (pthread_create(threads + i, NULL, floyd_warshall_worker,wa) != 0){
                    printf("floyd_warshall_parallel: error, could not"
                        " create a worker thread");
        }
        {
            cout<<"I am in a parallel" <<endl;
        }

        if (next_unassigned_row >= tops)
        {
            break;
        }
    }

	cout<<"the last";
    // Execute this thread's portion of the work
    floyd_warshall_fractional(next_unassigned_row,
                        next_unassigned_row + rows_per_thread - 1, sem_Array_of_Distance, tops, thread_count, Array_of_Distance, Array_of_History);

    // Rejoin other threads
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

}


void * floyd_warshall_worker(void * args)
{
	// worker_args &wa = *(static_cast<worker_args *>(args));

	worker_args_t  * wa =(worker_args_t  *)args; 
    
	cout<<"WORKERstarting "<< ((struct worker_args *)args)->starting_row<< " "<<wa->ending_row<<endl;

    floyd_warshall_fractional(wa->starting_row, wa->ending_row, wa->sem_Array_of_Distance, wa->vertex_count, wa->thread_count, wa->dist_Array_of_Distance, wa->dist_Array_of_History);
    pthread_exit(NULL);
	return NULL;
}


void floyd_warshall_fractional(int starting_row, int ending_row, sem_t *sem_Array_of_Distance, int tops, int thread_count, double** Array_Of_Distance, int** Array_Of_History)
{
	cout<< "starting ffffrow= "<< starting_row<<" ending= "<< ending_row<<endl;
    for (int i = starting_row; i <= ending_row; i++)
    {
		cout<< "starting ffffrow= "<< starting_row<<" ending= "<< ending_row<<endl;
        sem_wait((sem_Array_of_Distance + i));

        for (int j = 0; j < tops; j++)
        {
            for (int k = 0; k < tops; k++)
            {
                if (Array_Of_Distance[i][j] == INF)
                {
                    cout<<"Is INF!!"<<endl;
                    continue;
                }
                if (Array_Of_Distance[i][k] > Array_Of_Distance[i][j] + Array_Of_Distance[j][k])
                {
                    cout<<"change pos"<<endl;
                    Array_Of_Distance[i][k] = Array_Of_Distance[i][j] + Array_Of_Distance[j][k];
                    Array_Of_History[i][k] = Array_Of_History[i][j];

                }
            }

            if (i >= starting_row && i <= ending_row) 
            {
                for (int z = 0; z < thread_count; z++)
                {
                    sem_post(sem_Array_of_Distance + i + 1);
                }
            }
        }
    }
}
