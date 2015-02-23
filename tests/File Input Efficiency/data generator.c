#include <stdio.h>

#define MAX 10000000

int main()
{
    FILE *fin = fopen("test data", "w");
    int i;
    for (i = 0; i < MAX; ++i) {
        fprintf(fin, "%d\n", i);
    }
    
    return 0;
}