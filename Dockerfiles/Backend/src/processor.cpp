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
			this->Adjacency_Array[i][j] = INF;
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
	//else
	//{
	//	MessageBox::Show("Äàííûå íå ñ÷èòàíû. Ïðîâåðüòå êîððåêòíîñòü íàçâàíèÿ ôàéëà", "Âíèìàíèå!");
	//	return;
	//}


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
			if (i != j)
			{
				int a = rand() % 4;
				if (a == 0)
				{
					this->Adjacency_Array[i][j] = INF;
					continue;
				}
				this->Adjacency_Array[i][j] = rand() % 15 + 1;
				this->ribs++;
			}

		}
	}
}

void Processor::Set_Data_To_File(string File_Name)
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

	File.close();
	//MessageBox::Show("Äàííûå ñîõðàíåíû", "Âíèìàíèå!");
}

void Processor::Set_Path_To_File(string File_Name)
{

	ifstream From("Important/reserved_for_path.txt");
	ofstream To(File_Name);
	string temp;
	while (!From.eof())
	{
		temp = "";
		getline(From, temp);
		To << temp << endl;
	}
}

void Processor::Show_Graph()
{
	ofstream File("Important/picture.dot");
	File << "  digraph g{" << endl;
	File << "    dpi=\"600\";" << endl;
	File << "    rankdir=\"LR\";" << endl;
	File << "    splines=\"line\";" << endl;

	for (int i = 0; i < this->tops; i++)
	{
		File << "    " << i + 1 << " [shape=\"circle\"label=\"" << i + 1 << "\"];" << endl;
	}

	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			if (this->Adjacency_Array[i][j] != INF && i != j && this->Adjacency_Array[i][j] != 0)
			{
				File << "    " << i + 1 << "->" << j + 1 << " [weight=1000 label=\"" << Adjacency_Array[i][j] << "\"];" << endl;
			}
		}
	}
	File << "  }";
	File.close();
	remove("Important/picture.png");
	system("dot -Tpng -o Important/picture.png Important/picture.dot");
}

void Processor::Show_Path()
{
	ofstream File("Important/Path.dot");
	File << "  digraph g{" << endl;
	File << "    dpi=\"600\";" << endl;
	File << "    rankdir=\"LR\";" << endl;
	File << "    node[shape=circle, group=main];" << endl;


	for (int i = 0; i < this->path_counter - 1; i++)
	{
		File << "    " << this->path[i] << "->" << this->path[i + 1] << " [label=\"" << Adjacency_Array[this->path[i] - 1][this->path[i + 1] - 1] << "\"];" << endl;
	}
	File << "  }";
	File.close();
	remove("Important/Path.png");
	system("dot -Tpng -o Important/Path.png Important/Path.dot");
	SetPathToFile("Important/reserved_for_path.txt");
	delete[] this->path;

}


void Processor::Get_The_Shortest_Path_Floida()
{
	this->path = new int[this->tops]{};
	this->path_counter = 0;
	this->Floid = new Algorithm_Floida(this->tops, this->ribs, this->Adjacency_Array, this->from, this->to, this->path);
	Floid->Create_Arrays_of_Distance_History();
	Floid->Processing();
	Floid->Get_The_Shortest_Path();
	Floid->Set_Result_to_File();
	this->path_counter = Floid->counter;
	this->iterFloida = Floid->iterFloida;
	delete Floid;

}



bool Processor::is_INF(int row, int column)
{
	if (this->Adjacency_Array[row][column] == INF) return true;
	else return false;
}

void Processor::Set_Top_From(int From)
{
	this->from = From;
}

void Processor::Set_Top_To(int To)
{
	this->to = To;
}

void Processor::SetPathToFile(string File_Name)
{
	ofstream File(File_Name);
	File << "=========Êðàò÷àéøèé ïóòü îò " << this->from << " ê " << this->to << " âåðøèíå==========" << endl << endl;


	for (int i = 0; i < this->path_counter - 1; i++)
	{
		File << this->path[i] << "—>" << this->path[i + 1] << " = " << this->Adjacency_Array[this->path[i] - 1][this->path[i + 1] - 1] << endl;
	}
	File.close();

}




Processor::~Processor()
{
	for (int i = 0; i < this->tops; i++)
	{
		delete this->Adjacency_Array[i];
	}
}