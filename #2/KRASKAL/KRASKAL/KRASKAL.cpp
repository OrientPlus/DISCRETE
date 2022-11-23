#include "KRASKAL.h"

GRAPH::GRAPH(string _file_name) {
    file_name = _file_name;
    in.open(file_name);
    in >> gr_size;
    parent = new int[gr_size];

    picked.resize(gr_size);
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
    int uRep, vRep;
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
    for (int i = 0; i < G.size(); i++) {
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
    std::vector<int> st;
    bool fl = false;
    picked[0] = true;
    for (int i = 0; i < G.size(); i++)
    {
        if (G[i].second.first == 0)
            st.push_back(G[i].second.second);
        else
            break;
    }
    int _i = 0, it;
    for (_i; !st.empty(); _i++)
    {
        it = st[st.size()-1];
        st.pop_back();
        picked[it] = true;
        fl = false;
        for (int i = 0; i < G.size(); i++)
        {
            if (G[i].second.first != it && fl == false)
                continue;
            else if (G[i].second.first != it && fl == true)
                break;

            if (picked[G[i].second.second] == false && find(st.begin(), st.end(), G[i].second.second) == st.end())
            {
                st.push_back(G[i].second.second);
                fl = true;
            }
        }
    }
    for (int i = 0; i < gr_size; i++)
    {
        if (picked[i] == false)
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