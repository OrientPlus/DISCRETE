#include "KRASKAL.h"

GRAPH::GRAPH(string _file_name) {
    file_name = _file_name;
    in.open(file_name);
    in >> gr_size;
    parent = new int[gr_size];

    visited.resize(gr_size);
    //i 0 1 2 3 4 5
    //parent[i] 0 1 2 3 4 5
    for (int i = 0; i < gr_size; i++)
        parent[i] = i;

    weight_of_mst = 0;
    G.clear();
    T.clear();
}

void GRAPH::fill_graph()
{
    int weight;
    for(int i=0; i<gr_size; i++)
    {
        for (int j = 0; j < gr_size; j++)
        {
            in >> weight;
            if (weight == 0)
                continue;
            if (weight < 0)
                cout << "INF\n";
            G.push_back(make_pair(weight, edge(i, j)));
        }
    }
    in.close();
}


int GRAPH::find_set(int i) {
    // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
        // Else if i is not the parent of itself
        // Then i is not the representative of his set,
        // so we recursively call Find on its parent
        return find_set(parent[i]);
}

void GRAPH::union_set(int u, int v) {
    parent[u] = parent[v];
}
void GRAPH::kraskal() {
    int i, uRep, vRep;
    auto begin = std::chrono::steady_clock::now();
    int conn = check_connectivity();
    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    double _diff = diff;
    cout << "Execution time of the CHECK_CONNECTIVITY function: " << _diff / 1000000 << " sec." << endl;
    if (conn == 1)
    {
        cout << "\nThe graph is not connected!\n";
        return;
    }
  

    begin = std::chrono::steady_clock::now();
    sort(G.begin(), G.end()); // increasing weight
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]); // add to tree
            union_set(uRep, vRep);
            weight_of_mst += G[i].first;
        }
    }
    end = std::chrono::steady_clock::now();

    diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    _diff = diff;
    cout << "Execution time: " << _diff/1000000 << " sec." << endl;
    print();
}



int GRAPH::check_connectivity()
{
    in.open(file_name);
    vector<vector<int>> matrix;
    matrix.resize(gr_size);
    for (int i = 0; i < gr_size; i++)
        matrix[i].resize(gr_size);

    in.seekg(1);
    for (int i = 0; i < gr_size; i++)
    {
        for (int j = 0; j < gr_size; j++)
        {
            in >> matrix[i][j];
        }
    }

    std::vector<int> st;//исправить на инты и все ок
    visited[0] = true;
    for (int i = 0; i < G.size(); i++)
    {
        if (matrix[0][i] != 0)
            st.push_back(i); //и тута тоже на i заменить 
    }
    while (!st.empty())
    {
        int it = st[st.size() - 1];
        st.pop_back();
        visited[it] = true;
        for (int i = 0; i < gr_size; i++)
        {
            if (matrix[it][i] != 0 && visited[i] == false && find(st.begin(), st.end(), i) == st.end())
            {
                st.push_back(i);
            }
        }
    }
    for (int i = 0; i < gr_size; i++)
    {
        if (visited[i] == false)
            return 1;
    }
    return 0;
}

void GRAPH::print() {
    cout << "Weight of the spanning tree: " << weight_of_mst << endl;
    out.open("output.txt", std::ios::out);
    if (!out.is_open())
        cout << "\noutput file NOT OPEN!" << endl;
    for (int i = 0; i < T.size(); i++) {
        out << T[i].second.first << " - " << T[i].second.second << " : "
            << T[i].first;
        out << endl;
    }
}