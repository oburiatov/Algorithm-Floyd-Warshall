﻿#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
//#include"algorithmFloyd.h"
using namespace std;

//#define INF 1e9
class Algorithm_Floida;

class Processor
{
public:
	~Processor();
	void Create_Arrays();
	
	void Set_Data_Array_From_File(string File_Name);
	void Set_Data_Adjacency_Array_From_File(string File_Name);

	void Set_Data_Array_By_Generating(int num);
	void Set_Adjacency_Array_To_File(string File_Name);

	void Get_The_Shortest_Path_Floida();

	void Set_Top_From(int from);
	void Set_Top_To(int to);

	double** Adjacency_Array;
	int tops = NULL;
	int ribs = NULL;

    Algorithm_Floida* Floid = nullptr;

	double iterFloida = 0;
	int* path;
	int path_counter = 0;

	int from = NULL;
	int to = NULL;
	void SetPathToFile(string File_Name);//reserved data
};