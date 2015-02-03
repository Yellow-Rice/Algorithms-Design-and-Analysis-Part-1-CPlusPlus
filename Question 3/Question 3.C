#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_OF_NODES = 200;
const int NUM_OF_REPEAT = NUM_OF_NODES * NUM_OF_NODES * 8;
int ADJACENCY_MATRIX[NUM_OF_NODES][NUM_OF_NODES];
int TOTAL_NUM_OF_EDGES = 0;
int NUM_OF_EDGES[NUM_OF_NODES];

int karger_minimum_cut();
int random_contraction();


int main()
{
    for (int i = 0; i < NUM_OF_NODES; ++i) {
        for (int j = 0; j < NUM_OF_NODES; ++j) {
            ADJACENCY_MATRIX[i][j] = 0;
        }
        NUM_OF_EDGES[i] = 0;
    }
    TOTAL_NUM_OF_EDGES = 0;
    
    string line;
    istringstream is;
    int vertex1, vertex2;
    ifstream fin("kargerMinCut.txt");
    for (int i = 0; i < NUM_OF_NODES; ++i) {
        getline(fin, line);
        is.clear();
        is.str(line);
        is >> vertex1;
        --vertex1;
        while (is >> vertex2) {
            --vertex2;
            ++ADJACENCY_MATRIX[vertex1][vertex2];
            ++NUM_OF_EDGES[vertex1];
        }
        if (ADJACENCY_MATRIX[vertex1][vertex1] > 0) {
            NUM_OF_EDGES[vertex1] -= ADJACENCY_MATRIX[vertex1][vertex1];
            ADJACENCY_MATRIX[vertex1][vertex1] = 0;
        }
        TOTAL_NUM_OF_EDGES += NUM_OF_EDGES[vertex1];
    }
    TOTAL_NUM_OF_EDGES >>= 1;
    fin.close();
    
    cout << karger_minimum_cut() << endl;
    
    return 0;
}


int karger_minimum_cut()
{
    if (NUM_OF_NODES < 2) {
        return 0;
    }
    int current_minimum(INT_MAX), cut;
    srand(time(NULL));
    for (int i = 0; i < NUM_OF_REPEAT; ++i) {
        cut = random_contraction();
        current_minimum = cut < current_minimum ? cut : current_minimum;
    }
    
    return current_minimum;
}


int random_contraction()
{
    int adjacency_matrix[NUM_OF_NODES][NUM_OF_NODES];
    int num_of_edges[NUM_OF_NODES];
    int total_num_of_edges(TOTAL_NUM_OF_EDGES);
    int edge, vertex1, vertex2;
    for (int i = 0; i < NUM_OF_NODES; ++i) {
        for (int j = 0; j < NUM_OF_NODES; ++j) {
            adjacency_matrix[i][j] = ADJACENCY_MATRIX[i][j];
        }
        num_of_edges[i] = NUM_OF_EDGES[i];
    }
    
    for (int num_of_nodes = NUM_OF_NODES; num_of_nodes > 2; --num_of_nodes) {
        edge = rand() % total_num_of_edges + 1;
        vertex1 = vertex2 = 0;
        while (edge > num_of_edges[vertex1]) {
            edge -= num_of_edges[vertex1++];
        }
        while (edge > adjacency_matrix[vertex1][vertex2]) {
            edge -= adjacency_matrix[vertex1][vertex2++];
        };
        total_num_of_edges -= adjacency_matrix[vertex1][vertex2];
        num_of_edges[vertex1] += num_of_edges[vertex2] - adjacency_matrix[vertex1][vertex2] * 2;
        adjacency_matrix[vertex1][vertex2] = adjacency_matrix[vertex2][vertex1] = 0;
        num_of_edges[vertex2] = 0;
        for (int i = 0; i < NUM_OF_NODES; ++i) {
            if (adjacency_matrix[vertex2][i] > 0) {
                adjacency_matrix[vertex1][i] += adjacency_matrix[vertex2][i];
                adjacency_matrix[i][vertex1] = adjacency_matrix[vertex1][i];
                adjacency_matrix[vertex2][i] = adjacency_matrix[i][vertex2] = 0;
            }
        }
    }
    
    return total_num_of_edges;
}