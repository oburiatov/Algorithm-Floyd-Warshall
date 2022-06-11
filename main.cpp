#include<iostream>
#include<fstream>
#include<iomanip>
#include "processor.h"

using namespace std;

class Processor;

int main (int argc, char **argv)
{
    cout << "Hello Worfld";
    

    Processor a;
	a.tops = 300;
	a.Create_Arrays();
	a.Set_Top_From(8);
	a.Set_Top_To(3);
	a.Set_Data_Array_By_Generating(300);
	a.Get_The_Shortest_Path_Floida();
	// for (int i = 0; i < a.path_counter; i++)
	// {
	// 	cout << a.path[i] << endl;
	// }
}


