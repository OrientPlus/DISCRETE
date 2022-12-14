#pragma once

#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <chrono>

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

	std::vector<std::vector<int>> data;
	std::vector<unsigned long long> length;
	std::vector<bool> visited;
	std::vector<int> result;

	void print_result(auto exec_time);
	int get_next_vertex(int current);
};