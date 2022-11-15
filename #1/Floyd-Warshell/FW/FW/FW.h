#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <chrono>

#define INF INT_MAX


class FW {

public:
	FW(std::string path);
	~FW();

	void header();
private:
	std::fstream input;
	int gr_size,
		start_vertex, exit_it;

	std::vector<std::vector<int>> data;
	std::vector<unsigned long long> length;

	void print_result(auto exec_time);
};