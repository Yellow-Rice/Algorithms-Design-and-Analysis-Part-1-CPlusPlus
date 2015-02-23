#include <stdio.h>

int main()
{
    int max = -1;
    int counter = 0;
    int edge_counter[1000000];
    int reversed_edge_counter[1000000];
    int edge_max = 0;
    int reversed_edge_max = 0;
    int vertex1, vertex2;
    
    int i;
    for (i = 0; i < 1000000; ++i) {
        edge_counter[i] = reversed_edge_counter[i] = 0;
    }
    FILE *fin = fopen("SCC.txt", "r");
    while (fscanf(fin, "%d%d", &vertex1, &vertex2) != EOF) {
        if (vertex1 > max) {
            max = vertex1;
        }
        if (vertex2 > max) {
            max = vertex2;
        }
        ++counter;
        --vertex1;
        --vertex2;
        ++edge_counter[vertex1];
        ++reversed_edge_counter[vertex2];
    }
    
    printf("max = %d\n", max);
    printf("counter = %d\n", counter);
    for (i = 0; i < max; ++i) {
        if (edge_counter[i] > edge_max) {
            edge_max = edge_counter[i];
        }
        if (reversed_edge_counter[i] > reversed_edge_max) {
            reversed_edge_max = reversed_edge_counter[i];
        }
    }
    printf("edge_max = %d\n", edge_max);
    printf("reversed_edge_max = %d\n", reversed_edge_max);
    
    return 0;
}