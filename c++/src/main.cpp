#include<iostream>
#include<fstream>
#include <stdio.h>
#include<iomanip>
#include"processor.h"

using namespace std;


int main(int argc, char *argv[])
{
	// argv[0]- name of program
	// argv[1]- from what top start to search 
	// argv[2]- to what top search the shortest path
	// argv[3]- read from file or By Generating (file or gen)
	// argv[4]- how many tops to Generate (optional if chosen generating graph)
	// argv[5]- what option to use: parallel run or sequential

	string argv1 = argv[1];
	string argv2 = argv[2];
	string argv3 = argv[3];
	string argv4 = argv[4];
	string argv5 = argv[5];

	Processor proc;

	proc.Set_Top_From(stoi(argv1));
	proc.Set_Top_To(stoi(argv2));

	if(argv3=="file")
	{
		proc.Set_Data_Array_From_File("example.txt");
	}
	else if(argv3=="gen")
	{
		proc.Set_Data_Array_By_Generating(stoi(argv4));
		proc.Set_Adjacency_Array_To_File("adj_array.txt");
	}
	proc.Set_Treads(50);
	if(argv5=="parallel")
	{
		proc.Get_The_Shortest_Path_Paralleling_Floida();
	}
	else if(argv5=="sequential")
	{
		proc.Get_The_Shortest_Path_Floida();
	}

	proc.SetPathToFile("data.json", "result.json");

	
}


