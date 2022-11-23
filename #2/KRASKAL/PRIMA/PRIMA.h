#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <stack>

#define INF INT_MAX

using std::vector;
using std::string;
using std::fstream;
using std::pair;
using std::cout;
using std::cin;
using std::endl;

#define edge pair<int, int>

class GRAPH {
private:
    fstream in, out;
    vector<vector<int>> G; // graph
    vector<pair<int, edge>> T; // mst

    vector<bool> picked;

    string file_name;
    int weight_of_mst;
    int gr_size; // number of vertices/nodes in graph
public:
    GRAPH(string _file_name);
    int check_connectivity();

    void prima();
    void print();
};