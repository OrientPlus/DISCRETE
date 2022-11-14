#pragma once

#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <algorithm>

#define INF INT_MAX


class DEIJ {

public:
	DEIJ(std::string path);
	~DEIJ();

	void header();
private:
	std::fstream input;
	int gr_size,
		start_vertex;
	//int** data;

	std::vector<std::vector<int>> data;
	std::vector<unsigned long long> length;
	std::vector<bool> visited;
	std::vector<int> result;

	void print_result();
	std::vector<int>::iterator get_next_vertex(std::vector<int>::iterator current);
};