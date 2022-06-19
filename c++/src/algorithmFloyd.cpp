#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include"algorithmFloyd.h"
#include"parallel.h"

using namespace std;
#define INF 1e9


class Algorithm_Floida;

Algorithm_Floida::Algorithm_Floida(int tops, int ribs, double** Adjacency_Array, int from, int to, int* path, int thread_count)
{
	this->tops = tops;
	this->ribs = ribs;
	this->Adjacency_Array = Adjacency_Array;
	this->from = from;
	this->to = to;
	this->path = path;
	this->thread_count=thread_count;

}

void Algorithm_Floida::Create_Arrays_of_Distance_History()
{
	this->Array_Of_History = new int* [this->tops]{};
	this->Array_Of_Distance = new double* [this->tops]{};
	for (int i = 0; i < this->tops; i++)
	{
		this->Array_Of_History[i] = new int[this->tops]{};
		this->Array_Of_Distance[i] = new double[this->tops]{};
	}
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			if (i == j) {
				this->Array_Of_Distance[i][j] = INF;
			}
			else
			{
				this->Array_Of_Distance[i][j] = this->Adjacency_Array[i][j];
			}
			if (this->Array_Of_Distance[i][j] != INF) this->Array_Of_History[i][j] = j + 1;
		}
	}
}

void Algorithm_Floida::Processing()
{
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			if (i == j)this->Array_Of_Distance[i][j] = 0;
		}
	}
	
	for (int i = 0; i < this->tops; i++)
	{
		this->iterFloida++;
		for (int j = 0; j < this->tops; j++)
		{
			this->iterFloida++;
			if (this->Array_Of_Distance[i][j] != INF)
			{
				for (int k = 0; k < this->tops; k++)
				{
					this->iterFloida++;
					if (this->Array_Of_Distance[i][k] > this->Array_Of_Distance[i][j] + this->Array_Of_Distance[j][k])
					{
						this->Array_Of_Distance[i][k] = this->Array_Of_Distance[i][j] + this->Array_Of_Distance[j][k];
						this->Array_Of_History[i][k] = this->Array_Of_History[i][j];
					}
				}
			}
		}
	}
}

void Algorithm_Floida::Get_The_Shortest_Path()
{
	this->path[this->counter++] = this->from;
	int k = Array_Of_History[this->from - 1][this->to - 1];
	if (k != 0)
	{
		this->path[this->counter++] = k;
	}
	while (k != 0)
	{
		k = Array_Of_History[k - 1][to - 1];
		if (k != 0)
		{
			this->path[this->counter++] = k;
		}
	}
}

void Algorithm_Floida::Set_ArrayOfDistance_to_File()
{
	ofstream File("result.txt");
	File << "=====Result=====" << endl << endl;
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			File << setw(5) << Array_Of_Distance[i][j] << ends;
		}
		File << endl;
	}
	File.close();
}


void Algorithm_Floida::Get_The_Shortest_Path_Paralleling()
{
	for (int i = 0; i < tops; i++)
    {
        for (int j = 0; j < tops; j++)
        {
            cout<< this->Array_Of_Distance[i][j]<<"\t";
        }
        cout<<endl;
        
    }
	Get_The_Shortest_Path_Parallel(this->tops, this->thread_count, this->Array_Of_Distance, this->Array_Of_History);

}

Algorithm_Floida::~Algorithm_Floida()
{
	for (int i = 0; i < tops; i++)
	{
		delete[] Array_Of_Distance[i];
		delete[] Array_Of_History[i];
	}
	delete Array_Of_Distance;
	delete Array_Of_History;
}
