#include<iostream>
#include<fstream>
#include <stdio.h>
#include<iomanip>
#include"processor.h"

using namespace std;

//class Processor;
//class Algorithm_Floida;

int main(int argc, char *argv[])
{
	//argv[0]- name of program
	//argv[1]- from what top start to search 
	//argv[2]- to what top search the shortest path
	//argv[3]- read from file or By Generating
	//argv[4]- how many tops to Generate (optional if chosen generating graph)

	// string argv1 = argv[1];
	// string argv2 = argv[2];
	// string argv3 = argv[3];
	// string argv4 = argv[4];

	Processor proc;

	// proc.Set_Top_From(stoi(argv1));
	// proc.Set_Top_To(stoi(argv2));

	// if(argv3=="file")
	// {
	// 	proc.Set_Data_Array_From_File("example.txt");
	// }
	// else if(argv3=="gen")
	// {
	// 	proc.Set_Data_Array_By_Generating(stoi(argv4));
	// 	proc.Set_Adjacency_Array_To_File("adj_array.txt");
	// }


	proc.Set_Top_From(5);
	proc.Set_Top_To(6);
	proc.Set_Treads(50);
	// proc.Set_Data_Array_From_File("example.txt");
	proc.Set_Data_Array_By_Generating(1000);
	
	proc.Get_The_Shortest_Path_Paralleling_Floida();
	

	// proc.Get_The_Shortest_Path_Floida();

	proc.SetPathToFile("result.txt");
	
	// delete
	//  for (int i = 0; i < proc.path_counter; i++)
	//  {
	//  	cout << proc.path[i] << endl;
	//  }
}


