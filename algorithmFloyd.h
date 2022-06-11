#pragma once
#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>


using namespace std;
#define INF 1e9;

class Algorithm_Floida
{
public:
	Algorithm_Floida(int tops, int ribs, double** Adjacency_Array);
	int tops;
	int ribs;
	int from=6;
	int to=1;
    
	double** Adjacency_Array;
	double** Array_Of_Distance;
	int** Array_Of_History;
	void Create_Arrays_of_Distance_History();
	void Processing();
	void Get_Array_of_Distance();
	void Get_The_Shortest_Path();
	void Set_Result_to_File();
	~Algorithm_Floida();
};