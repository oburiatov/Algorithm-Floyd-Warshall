#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include"processor.h"
#include"algorithmFloyd.h"
#include<sys/time.h>

using namespace std;
#define INF 1e9

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
	int a=0;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (i != j&& (Adjacency_Array[j][i]==0 || Adjacency_Array[j][i]==INF))
			{
				a = rand() % 5;
				if (a != 0)
				{
					this->Adjacency_Array[i][j] = INF;
					continue;
				}
				else {
				this->Adjacency_Array[i][j] = rand() % 15 + 1;
				this->ribs++;
				}

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
	gettimeofday(&this->startTime,0);
	Floid->Processing();
	gettimeofday(&this->endTime, 0);
	this->spentTime=1000000*(this->endTime.tv_sec - this->startTime.tv_sec)+ (this->endTime.tv_usec - this->startTime.tv_usec);
	this->spentTime/=1000000;
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
	gettimeofday(&this->startTime,0);
	Floid->Processing_In_Parallel();
	gettimeofday(&this->endTime, 0);
	this->spentTime=1000000*(this->endTime.tv_sec - this->startTime.tv_sec)+ (this->endTime.tv_usec - this->startTime.tv_usec);
	this->spentTime/=1000000;
	Floid->Get_The_Shortest_Path();
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

void Processor::SetPathToFile(string data, string result)
{
	ofstream File(data);
	File<<"[";
	for (int i = 0; i < tops; i++)
	{	
		for (int j = 0; j < tops; j++)
		{
			if(Adjacency_Array[i][j]!=0 &&Adjacency_Array[i][j]!=INF)
			{
				File<<"{\"source\": \""<<i+1<<"\", \"target\": \""<<j+1<<"\", \"value\": \""<<Adjacency_Array[i][j]<<"\", \"color\": \"black"<<"\" },";
			}
		}
		
	}
	File<<"{}";
	File<<"]"<<endl;
	File.close();

	ofstream res(result);
	res<<"[";
	
	for (int i = 0; i < this->path_counter - 1; i++)
	{
		res<<"{\"source\": \""<<this->path[i]<<"\", \"target\": \""<<this->path[i + 1]<<"\", \"value\": \""<<this->Adjacency_Array[this->path[i] - 1][this->path[i + 1] - 1]<<"\", \"color\": \"red"<<"\" },";
	}
	res<<"{\"time\": \""<<this->spentTime<<"\" }";
	res<<"]"<<endl;
	res.close();
}

Processor::~Processor()
{
	for (int i = 0; i < this->tops; i++)
	{
		delete this->Adjacency_Array[i];
	}
}