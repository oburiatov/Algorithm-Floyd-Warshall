#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include"processor.h"
#include"algorithmFloyd.h"

using namespace std;
#define INF 4294967295U

class Processor;
class Algorithm_Floida;

void Processor::Create_Arrays()
{
	this->Adjacency_Array = new double* [this->tops];
	for (int i = 0; i < tops; i++)
	{
		this->Adjacency_Array[i] = new double[this->tops]{};
	}
	for (int i = 0; i < this->tops; i++)
	{
		for (int j = 0; j < this->tops; j++)
		{
			this->Adjacency_Array[i][j] =  INF;
		}
	}
}

void Processor::Set_Data_Array_From_File(string File_Name)
{
	int x;
	int y;
	double weight;
	ifstream File(File_Name);
	File >> this->tops;
	File >> this->ribs;
	this->Adjacency_Array = new double* [this->tops];
	Create_Arrays();
	for (int i = 0; i < ribs; i++)
	{
		File >> x;
		File >> y;
		File >> weight;
		this->Adjacency_Array[x - 1][y - 1] = weight;
	}
}

void Processor::Set_Data_Adjacency_Array_From_File(string File_Name)
{
	ifstream File(File_Name);
	if (File.is_open())
	{
		File >> this->tops;
		double data;
		Create_Arrays();
		File >> this->ribs;
		for (int i = 0; i < this->tops; i++)
		{
			for (int j = 0; j < this->tops; j++)
			{
				File >> data;
				this->Adjacency_Array[i][j] = data;
			}
		}
	}
}

void Processor::Set_Data_Array_By_Generating(int num)
{
	this->tops = num;
	this->Adjacency_Array = new double* [tops];
	Create_Arrays();
	srand(time(NULL));
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (i != j)
			{
				int a = rand() % 4;
				if (a == 0)
				{
					this->Adjacency_Array[i][j] = INF;
					continue;
				}
				this->Adjacency_Array[i][j] = rand() % 15 + 1;
				this->ribs++;
			}
		}
	}
}

void Processor::Set_Adjacency_Array_To_File(string File_Name)
{
	ofstream File(File_Name);
	File << this->tops << " ";
	File << this->ribs << endl;
	for (int i = 0; i < this->tops; i++)
	{
		for (int j = 0; j < this->tops; j++)
		{
			File << setw(10) << this->Adjacency_Array[i][j];
		}
		if (i != this->tops - 1)File << endl;
	}
	File<<endl;
	File.close();
}
void Processor::Set_Treads(int thread_num){
	this->tread_num=thread_num;
}



void Processor::Get_The_Shortest_Path_Floida()
{
	this->path = new int[this->tops]{};
	this->path_counter = 0;
	this->Floid = new Algorithm_Floida(this->tops, this->ribs, this->Adjacency_Array, this->from, this->to, this->path, this->tread_num);
	Floid->Create_Arrays_of_Distance_History();
	Floid->Processing();
	Floid->Get_The_Shortest_Path();
	Floid->Set_ArrayOfDistance_to_File();
	this->path_counter = Floid->counter;
	this->iterFloida = Floid->iterFloida;
	delete Floid;
}

void Processor::Get_The_Shortest_Path_Paralleling_Floida()
{
	this->path = new int[this->tops]{};
	this->path_counter = 0;
	this->Floid = new Algorithm_Floida(this->tops, this->ribs, this->Adjacency_Array, this->from, this->to, this->path, this->tread_num);
	Floid->Create_Arrays_of_Distance_History();
	Floid->Get_The_Shortest_Path_Paralleling();
	Floid->Set_ArrayOfDistance_to_File();
	this->path_counter = Floid->counter;
	this->iterFloida = Floid->iterFloida;
	delete Floid;
}

void Processor::Set_Top_From(int From)
{
	this->from = From;
}

void Processor::Set_Top_To(int To)
{
	this->to = To;
}

void Processor::SetPathToFile(string File_Name)
{
	ofstream File(File_Name);
	File << "=========The shortest path from " << this->from << " to " << this->to << ": " << endl << endl;

	for (int i = 0; i < this->path_counter - 1; i++)
	{
		File << this->path[i] << "—>" << this->path[i + 1] << " = " << this->Adjacency_Array[this->path[i] - 1][this->path[i + 1] - 1] << endl;
	}
	File.close();
}


Processor::~Processor()
{
	for (int i = 0; i < this->tops; i++)
	{
		delete this->Adjacency_Array[i];
	}
}