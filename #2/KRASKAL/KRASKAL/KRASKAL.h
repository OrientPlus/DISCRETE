#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <stack>

#define edge pair<int,int>

using std::vector;
using std::string;
using std::fstream;
using std::pair;
using std::cout;
using std::cin;
using std::endl;

#define edge pair<int,int>

class GRAPH {
private:
    fstream in, out;
    vector<pair<int, edge>> G; // graph
    vector<pair<int, edge>> T; // mst
    
    vector<bool> visited;

    string file_name;
    int* parent, weight_of_mst;
    int gr_size; // number of vertices/nodes in graph
public:
    GRAPH(string _file_name);
    void fill_graph();
    int check_connectivity();

    int find_set(int i);
    void union_set(int u, int v);
    void kraskal();
    void print();
};