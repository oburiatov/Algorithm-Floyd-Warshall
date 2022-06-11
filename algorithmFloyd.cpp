#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include"algorithmFloyd.h"

using namespace std;
#define INF 1e9

class Algorithm_Floida;

Algorithm_Floida::Algorithm_Floida( int tops, int ribs, double** Adjacency_Array)
{
	this->tops = tops;
	this->ribs = ribs;
	this->Adjacency_Array = Adjacency_Array;
}



void Algorithm_Floida::Create_Arrays_of_Distance_History()
{
	this->Array_Of_History = new int*[this->tops]{};
	this->Array_Of_Distance = new double*[this->tops]{};
	
	for (int i = 0; i < this->tops; i++)
	{
		this->Array_Of_History[i] = new int[this->tops] {};
		this->Array_Of_Distance[i] = new double[this->tops] {};
	}
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			this->Array_Of_Distance[i][j] = this->Adjacency_Array[i][j];
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
		for (int j = 0; j < this->tops; j++)
		{
			if (this->Array_Of_Distance[i][j] != INF)
			{
				for (int k = 0; k < this->tops; k++)
				{
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

void Algorithm_Floida::Get_Array_of_Distance()
{
	for (int i = 0; i < this->tops; i++)
	{
		for (int j = 0; j < this->tops; j++)
		{
			cout << this->Array_Of_Distance[i][j] << '\t';
		}
		cout << endl;
	}
}

void Algorithm_Floida::Get_The_Shortest_Path()
{
	cout << "Find the shortest path: from " << from << " to " << to << ":" << endl;
	cout << from << '\t';
	int k = Array_Of_History[from - 1][to - 1];
	while (k != 0)
	{
		cout << k << '\t';
		k = Array_Of_History[k - 1][to - 1];
	}
	cout << endl;
}

void Algorithm_Floida::Set_Result_to_File()
{
	ofstream File("result.txt");
	File << "=====Hello=====" << endl<<endl;
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			File <<setw(5)<< Array_Of_Distance[i][j] << ends;
		}
		File << endl;
	}

	File.close();
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
	cout << "Destructor" << endl;

}