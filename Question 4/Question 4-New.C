#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX = 875714;
int leaders[MAX];
vector<vector<int> > adjacency_list(MAX);
vector<vector<int> > reversed_adjacency_list(MAX);
int finish_time[MAX];
int current_time;
int current_source;
int counter;
int max_scc[5] = {0, 0, 0, 0, 0};

void DFS_1(int n) {
    leaders[n] = current_source;
    for (int i = 0; i < adjacency_list[n].size(); ++i) {
        if (leaders[adjacency_list[n][i]] < 0) {
            DFS_1(adjacency_list[n][i]);
        }
    }
    finish_time[current_time++] = n;
}

void DFS_LOOP_1()
{
    for (int i = 0; i < MAX; ++i) {
        leaders[i] = -1;
    }
    current_time = 0;
    for (int i = MAX - 1; i >= 0; --i) {
        if (leaders[i] < 0) {
            current_source = i;
            DFS_1(i);
        }
    }
}

void DFS_2(int n) {
    leaders[n] = current_source;
    ++counter;
    for (int i = 0; i <  reversed_adjacency_list[n].size(); ++i) {
        if (leaders[reversed_adjacency_list[n][i]] < 0) {
            DFS_2(reversed_adjacency_list[n][i]);
        }
    }
}

void DFS_LOOP_2()
{
    for (int i = 0; i < MAX; ++i) {
        leaders[i] = -1;
    }
    for (int i = MAX - 1; i >= 0; --i) {
        if (leaders[finish_time[i]] < 0) {
            current_source = finish_time[i];
            counter = 0;
            DFS_2(finish_time[i]);
            if (counter > max_scc[4]) {
                int j;
                for (j = 4; j > 0 && counter > max_scc[j - 1]; --j) {
                    max_scc[j] = max_scc[j - 1];
                }
                max_scc[j] = counter;
            }
        }
    }
}

int main()
{
    fstream fin("SCC.txt");
    int vertex1, vertex2;
    while (fin >> vertex1 >> vertex2) {
        adjacency_list[--vertex1].push_back(--vertex2);
        reversed_adjacency_list[vertex2].push_back(vertex1);
    }
    fin.close();
    
    DFS_LOOP_1();
    DFS_LOOP_2();
    
    cout << max_scc[0];
    for (int i = 1; i < 5; ++i) {
        cout << ',' << max_scc[i];
    }
    cout << endl;
    cout << sizeof(adjacency_list) << endl;
    
    return 0;
}
