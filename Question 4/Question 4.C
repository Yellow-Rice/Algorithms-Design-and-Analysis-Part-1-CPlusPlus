#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    int vertex;
    Node* next;
    Node(int v = -1, Node* n = NULL) : vertex(v), next(n) {}
};

const int MAX = 875714;
int leaders[MAX];
Node adjacency_list[MAX];
Node reversed_adjacency_list[MAX];
Node *tails[MAX];
Node *reversed_tails[MAX];
int finish_time[MAX];
int current_time;
int current_source;
int counter;
int max_scc[5] = {0, 0, 0, 0, 0};

void DFS_1(int i) {
    leaders[i] = current_source;
    for (Node *n = reversed_adjacency_list[i].next; n != NULL; n = n -> next) {
        if (leaders[n -> vertex] < 0) {
            DFS_1(n -> vertex);
        }
    }
    finish_time[current_time++] = i;
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

void DFS_2(int i) {
    leaders[i] = current_source;
    ++counter;
    for (Node *n = adjacency_list[i].next; n != NULL; n = n -> next) {
        if (leaders[n -> vertex] < 0) {
            DFS_2(n -> vertex);
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
    for (int i = 0; i < MAX; ++i) {
        adjacency_list[i].next = reversed_adjacency_list[i].next = NULL;
        tails[i] = adjacency_list + i;
        reversed_tails[i] = reversed_adjacency_list + i;
    }
    while (fin >> vertex1 >> vertex2) {
        --vertex1;
        --vertex2;
        tails[vertex1] -> next = new Node(vertex2);
        tails[vertex1] = tails[vertex1] -> next;
        reversed_tails[vertex2] -> next = new Node(vertex1);
        reversed_tails[vertex2] = reversed_tails[vertex2] -> next;
    }
    fin.close();
    
    DFS_LOOP_1();
    DFS_LOOP_2();
    
    for (int i = 0, j; i < MAX; ++i) {
        j = 0;
        for (Node *n = adjacency_list[i].next; n != NULL; n = n -> next) {
            tails[j++] = n;
        }
        for (int k = 0; k < j; ++k) {
            delete tails[k];
        }
        j = 0;
        for (Node *n = reversed_adjacency_list[i].next; n != NULL; n = n -> next) {
            reversed_tails[j++] = n;
        }
        for (int k = 0; k < j; ++k) {
            delete reversed_tails[k];
        }
    }
    
    cout << max_scc[0];
    for (int i = 1; i < 5; ++i) {
        cout << ',' << max_scc[i];
    }
    cout << endl;
    
    return 0;
}
