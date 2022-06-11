#pragma once
#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include"algorithmFloyd.h"
using namespace std;

#define INF 1e9
class Algorithm_Floida;

class Processor
{
public:
	void Set_Top_From(int from);
	void Set_Top_To(int to);


	void Create_Arrays();
	void Set_Data_Array_From_File(string File_Name);
	void Set_Data_Array_By_Inputing(int num);
	void Set_Data_Array_By_Generating(int num);

	void Get_The_Shortest_Path_Floida();
	void Get_The_Shortest_Path_Dantzig();

	~Processor();
// private:
	int tops;
	int ribs;

	int from = NULL;
	int to = NULL;

    int path_counter = 0;
	double** Adjacency_Array;
    Algorithm_Floida* Floid = nullptr;
};