#pragma once
#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>
#include<semaphore.h>


using namespace std;
#define INF 1e9;

class Algorithm_Floida
{
public:
	Algorithm_Floida(int tops, int ribs, double** Adjacency_Array, int from, int to, int* path, int thread_count);
	void Create_Arrays_of_Distance_History();
	void Processing();
	void Processing_In_Parallel();
	void Get_The_Shortest_Path();
	void Set_ArrayOfDistance_to_File();
	double iterFloida = 0;
	int counter = 0;

	~Algorithm_Floida();
private:
	int tops = NULL;
	int ribs;

	int from = NULL;
	int to = NULL;
	int* path;
	int thread_count = 0;
	double** Adjacency_Array;
	double** Array_Of_Distance;
	int** Array_Of_History;
};