#include<iostream>
#include<fstream>
#include<iomanip>
#include"processor.h"
#include"algorithmFloyd.h"

using namespace std;

//class Processor;
//class Algorithm_Floida;

int main()
{
	
	Processor a;
	a.Set_Top_From(7);
	a.Set_Top_To(1);
	a.Set_Data_Array_By_Generating(1000);
	//a.Set_Data_Array_From_File("data.txt");
	a.Get_The_Shortest_Path_Floida();
	 for (int i = 0; i < a.path_counter; i++)
	 {
	 	cout << a.path[i] << endl;
	 }
}


