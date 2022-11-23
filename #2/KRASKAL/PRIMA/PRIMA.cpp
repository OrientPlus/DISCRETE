#include "PRIMA.h"

GRAPH::GRAPH(string _file_name) {
    file_name = _file_name;
    in.open(file_name);
    in >> gr_size;

    picked.resize(gr_size);
    G.resize(gr_size);
    for (int i = 0; i < gr_size; i++)
        G[i].resize(gr_size);
    T.reserve(gr_size);

    int weight;
    for (int i = 0; i < gr_size; i++)
    {
        for (int j = 0; j < gr_size; j++)
        {
            in >> weight;
            if (weight == 0)
                G[i][j] = INF;
            else
                G[i][j] = weight;
        }
    }
    in.close();

    weight_of_mst = 0;
}

void GRAPH::prima() {
    int x = 0, y = 0;

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
    picked[0] = true;
    int size_picked = 1, cur_count_SP =0;

    vector<int>::iterator it;
    for (int k = 0; k < gr_size-1; k++)
    {
        int min = INF;
        x = 0;
        y = 0;
        for (int i = 0; i < gr_size; i++)
        {
            if (picked[i])
            {
                for (int j = 0; j < gr_size; j++)
                {
                    if (!picked[j] && G[i][j] != INF)
                    {
                        if (min > G[i][j])
                        {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
                cur_count_SP++;
            }
            else if (cur_count_SP == size_picked)
                break;
        }
        weight_of_mst += G[x][y];
        T.push_back(make_pair(G[x][y], edge(x,y)));
        picked[y] = true;
        size_picked++;
        cur_count_SP = 0;
    }

    end = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    _diff = diff;
    cout << "Execution time: " << _diff / 1000000 << " sec." << endl;
    print();
}



int GRAPH::check_connectivity()
{
    std::vector<int> st;
    bool fl = false;
    vector<bool> _visited;
    _visited.resize(gr_size);
    for (int i = 0; i < gr_size; i++)
        _visited[i] = false;
   
    _visited[0] = true;
    for (int i = 0; i < G.size(); i++)
    {
        if (G[0][i] != INF)
            st.push_back(i);
    }
    while (!st.empty())
    {
        int it = st[st.size() - 1];
        st.pop_back();
        _visited[it] = true;
        for (int i = 0; i < gr_size; i++)
        {
            if (G[it][i] == INF)
                continue;
            if (_visited[i] == false && find(st.begin(), st.end(), i) == st.end())
            {
                st.push_back(i);
            }
        }
    }
    for (int i = 0; i < gr_size; i++)
    {
        if (_visited[i] == false)
            return 1;
    }
    return 0;
}

void GRAPH::print() {
    cout << "Weight of the spanning tree: " << weight_of_mst << endl;
    out.open("output.txt", std::ios::out);
    out << "Weight of the spanning tree: " << weight_of_mst << endl;
    if (!out.is_open())
        cout << "\noutput file NOT OPEN!" << endl;
    for (int i = 0; i < T.size(); i++) {
        out << T[i].second.first << " - " << T[i].second.second << " : "
            << T[i].first;
        out << endl;
    }
}