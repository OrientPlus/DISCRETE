#include "Deij_alg.h"

namespace fs = std::filesystem;
using namespace std;

DEIJ::DEIJ(string path)
{
	gr_size = 0;
	start_vertex = 0;
	if (!fs::exists(path))
	{
		cout << "\nA file with that name does not exist!" << endl;
		system("pause");
		exit(-1);
	}
	input.open(path);
	
	//получаем размер и выделяем память
	input >> gr_size;
	visited.reserve(gr_size);
	length.reserve(gr_size);
	
	data.resize(gr_size);
	for (int j = 0; j < gr_size; j++)
		data[j].resize(gr_size);
	for (int i = 0; i < gr_size; i++)
	{
		data[i].push_back(INF);
		length.push_back(INF);
		visited.push_back(false);
	}
}

DEIJ::~DEIJ()
{

}

void DEIJ::header()
{
	//заполняем данные о графе
	for (int i = 0; i < gr_size; i++)
	{
		for (int j = 0; j < gr_size; j++)
		{
			input >> data[i][j];
			if (data[i][j] == 0)
			{
				data[i][j] = INF;
				continue;
			}
			if (data[i][j] < 0)
			{
				cout << "\nERROR! Negative value!" << endl;
				system("pause");
				exit(-1);
			}
		}
	}

	cout << "Enter the starting vertex: ";
	cin >> start_vertex;
	if (start_vertex >= gr_size)
	{
		cout << "There is no vertex with this number! Maximum vertex number: " << gr_size - 1 << " The default value of 0 will be used.";
		start_vertex = 0;
	}
	length[start_vertex] = 0;

	auto begin = chrono::steady_clock::now();
	int current_vertex = start_vertex;
	for (int i = 0; i < gr_size; i++)
	{
		for (int j = 0; j < gr_size; j++)
		{
			if (current_vertex == -1)
				break;

			if (data[current_vertex][j] == INF || visited[j] == true)
				continue;
			
			if (length[j] > length[current_vertex] + data[current_vertex][j])
				length[j] = length[current_vertex] + data[current_vertex][j];
		}
		if (current_vertex != -1)
		{
			visited[current_vertex] = true;
			current_vertex = get_next_vertex(current_vertex);
		}
		else
			break;
	}

	auto end = chrono::steady_clock::now();
	auto exec_time = chrono::duration_cast<chrono::milliseconds>(end - begin);
	print_result(exec_time);
}

void DEIJ::print_result(auto exec_time)
{
	ofstream out("output.txt");
	cout << "\nRESULT FROM " << start_vertex << " VERTEX: " << endl;
	out << "\nRESULT FROM " << start_vertex << " VERTEX: " << endl;
	for (int i = 0; i < gr_size; i++)
	{
		if (length[i] == INF)
		{
			out << "INF   ";
			cout << "INF   ";
		}
		else
		{
			out << length[i] << "   ";
			cout << length[i] << "  ";
		}
		if (i % 25 == 0)
		{
			cout << endl;
			out << endl;
		}
	}
	
	cout << "\nExecution time: ";
	out << "\nExecution time: ";
	if (exec_time.count() > 1000)
	{
		cout << exec_time.count()/1000 << " seconds" << endl;
		out << exec_time.count() / 1000 << " seconds" << endl;
	}
	else {
		cout << exec_time.count() << " milliseconds." << endl;
		out << exec_time.count() << " milliseconds." << endl;
	}
	
	return;
}

int DEIJ::get_next_vertex(int current)
{
	static int old_vertex = INF;
	if (old_vertex == INF)
		old_vertex = current;

	int min = INF, min_ind = -1;
	for (int i = 0; i < gr_size; i++)
	{
		if (data[old_vertex][i]!= INF && visited[i] == false)
		{
			break;
		}
		if (i == gr_size - 1)
		{
			for (int j = 0; j < gr_size; j++)
			{
				if (data[old_vertex][j] < min)
				{
					min = data[old_vertex][j];
					min_ind = j;
				}
			}
			old_vertex = min_ind;
		}
	}

	min = INF; min_ind = -1;
	for (int i = 0; i < gr_size; i++)
	{
		if (data[old_vertex][i] < min && visited[i] == false)
		{
			min = data[old_vertex][i];
			min_ind = i;
		}
	}

	return min_ind;
}
