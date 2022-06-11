#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include"processor.h"
#include"algorithmFloyd.h"

using namespace std;
#define INF 1e9

class Processor;
class Algorithm_Floida;



void Processor::Set_Top_From(int From)
{
	this->from = From;
}

void Processor::Set_Top_To(int To)
{
	this->to = To;
}


void Processor::Create_Arrays()
{
	this->Adjacency_Array= new double*[this->tops];
	for (int i = 0; i < tops; i++)
	{
		this->Adjacency_Array[i] = new double[this->tops]{};
	}
	for (int i = 0; i < this->tops; i++)
	{
		for (int j = 0; j < this->tops; j++)
		{
			this->Adjacency_Array[i][j] = INF;
		}
	}
}

void Processor::Set_Data_Array_From_File(string File_Name)
{
	int x;
	int y;
	double weight;
	ifstream File("data.txt");
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
			this->Adjacency_Array[i][j] = rand() % 100 - 50;
		}
	}
}


void Processor::Set_Data_Array_By_Inputing(int num)
{
	this->tops = num;
	Create_Arrays();
	double temp;

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			cin >> temp;
			this->Adjacency_Array[i][j] = temp;
		}
	}

}

void Processor::Get_The_Shortest_Path_Floida()
{
	this->Floid = new Algorithm_Floida(this->tops, this->ribs, this->Adjacency_Array);
	Floid->Create_Arrays_of_Distance_History();
	Floid->Processing();
	Floid->Get_Array_of_Distance();
	Floid->Get_The_Shortest_Path();
	Floid->Set_Result_to_File();
	delete Floid;
}


Processor::~Processor()
{
	for (int i = 0; i < tops; i++)
	{
		delete this->Adjacency_Array[i];
	}
	cout << "Data Destructor" << endl;
}
