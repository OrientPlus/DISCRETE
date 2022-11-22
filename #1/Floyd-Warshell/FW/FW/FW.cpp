#include "FW.h"

namespace fs = std::filesystem;
using namespace std;

FW::FW(string path)
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

	//получаем размер и выдел€ем пам€ть
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

FW::~FW()
{

}

void FW::header()
{
	//заполн€ем данные о графе
	for (int i = 0; i < gr_size; i++)
	{
		for (int j = 0; j < gr_size; j++)
		{
			input >> data[i][j];
			if (data[i][j] == 0 && i != j)
			{
				data[i][j] = INF;
				continue;
			}
			if (data[i][j] < 0)
				cout << "WARNING! Negative cycle!" << endl;
		}
	}

	auto begin = chrono::steady_clock::now();
	int current_vertex = start_vertex;
	
	for (int k = 0; k < gr_size; k++) {	//ѕробегаемс€ по всем вершинам и ищем более короткий путь через вершину k
		for (int i = 0; i < gr_size; i++) {
			for (int j = 0; j < gr_size; j++) {

				if (data[i][j] > data[i][k] + data[k][j] && data[i][k] != INF && data[k][j] != INF)
					data[i][j] = data[i][k] + data[k][j];
				//data[i][j] = std::min(data[i][j], data[i][k] + data[k][j]);	//Ќовое значение ребра равно минимальному между старым ребром и суммой ребер 
			}
		}
	}

	auto end = chrono::steady_clock::now();
	auto exec_time = chrono::duration_cast<chrono::milliseconds>(end - begin);
	print_result(exec_time);
}

void FW::print_result(auto exec_time)
{
	ofstream out("output.txt");
	for (int i = 0; i < gr_size; i++)
	{
		for (int j = 0; j < gr_size; j++)
		{
			if (data[i][j] == INF)
			{
				out << "INF   ";
				//cout << "INF   ";
			}
			else
			{
				out << data[i][j] << " ";
				//cout << data[i][j] << " ";
			}
		}
		//cout << endl;
		out << endl;
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