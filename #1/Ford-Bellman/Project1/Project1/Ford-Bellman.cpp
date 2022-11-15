#include "Ford-Bellman.h"

namespace fs = std::filesystem;
using namespace std;

FB::FB(string path)
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
	length.reserve(gr_size);

	data.resize(gr_size);
	for (int j = 0; j < gr_size; j++)
		data[j].resize(gr_size);
	for (int i = 0; i < gr_size; i++)
	{
		data[i].push_back(INF);
		length.push_back(INF);
	}
}

FB::~FB()
{

}

void FB::header()
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
				cout << "WARNING! Negative value!" << endl;
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
	vector<unsigned long long> old_length;
	auto begin = chrono::steady_clock::now();
	int current_vertex = start_vertex;
	bool break_fl = false;
	for (int i = 0; i < gr_size-1; i++)
	{
		if (break_fl)
		{
			exit_it = i;
			break;
		}

		for (int j = 0; j <= i; j++)
		{
			//бежим по матрице смежности
			for (int k = 0; k < gr_size; k++)
			{
				for (int f = 0; f < gr_size; f++)
				{
					if (data[k][f] != INF)
					{
						if (length[k] > length[f] + data[k][f])
							length[k] = length[f] + data[k][f];
					}
				}
			}
		}

		//завершаем алгоритм раньше, если уже найдены оптимальные пути
		if (i%5==0 && i != 0)
		{
			for (int k = 0; k < gr_size; k++)
			{
				if (k == gr_size - 1 && old_length[k] == length[k])
					break_fl = true;
				if (old_length[k] == length[k])
					continue;
				else
					break;
			}
		}
		old_length = length;
	}

	auto end = chrono::steady_clock::now();
	auto exec_time = chrono::duration_cast<chrono::milliseconds>(end - begin);
	print_result(exec_time);
}

void FB::print_result(auto exec_time)
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
		cout << exec_time.count() / 1000 << " seconds" << endl;
		out << exec_time.count() / 1000 << " seconds" << endl;
	}
	else {
		cout << exec_time.count() << " milliseconds." << endl;
		out << exec_time.count() << " milliseconds." << endl;
	}

	cout << "Exit on " << exit_it << " iteration";

	return;
}
