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
				cout << data[i][j] << " ";
				continue;
			}
			if (data[i][j] < 0)
			{
				cout << "\nERROR! Negative value!" << endl;
				exit(-1);
			}
			cout << data[i][j] << "          ";
		}
		cout << endl;
	}

	cout << "Enter the starting vertex: ";
	cin >> start_vertex;
	if (start_vertex >= gr_size)
	{
		cout << "There is no vertex with this number! Maximum vertex number: " << gr_size - 1 << " The default value of 0 will be used.";
		start_vertex = 0;
	}
	length[start_vertex] = 0;

	int min_len = INF, current_vertex = start_vertex;
	vector<int>::iterator it = data[current_vertex].begin();
	for (int i = 0; i < gr_size; i++)
	{
		for (int j = 0; j < gr_size; j++)
		{
			if (it[j] == INF || visited[j] == true)
				continue;
			if (it[j] < min_len)
				min_len = it[j];
			
			if (length[j] > length[current_vertex] + it[j])
				length[j] = length[current_vertex] + it[j];
		}
		it = get_next_vertex(it);
		visited[current_vertex] = true;
	}

	print_result();
}

void DEIJ::print_result()
{
	cout << "\nRESULT FROM " << start_vertex << " VERTEX: ";
	for (int i = 0; i < gr_size; i++)
		cout << length[i] << "  ";
	
	return;
}

vector<int>::iterator DEIJ::get_next_vertex(vector<int>::iterator current)
{
	vector<int>::iterator it;
	int min = INF, min_ind = -1;
	for (int i = 0; i < gr_size; i++)
	{
		if (current[i] < min)
		{
			min = current[i];
			min_ind = i;
		}
	}
	
	it = data[min_ind].begin();
	return it;
}
