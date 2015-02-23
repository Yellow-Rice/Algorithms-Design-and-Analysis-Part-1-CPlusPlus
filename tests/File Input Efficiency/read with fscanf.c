#include <stdio.h>

int main()
{
    FILE *fin = fopen("test data", "r");
    int i;
    while (fscanf(fin, "%d", &i) != EOF) {
        continue;
    }
    fclose(fin);
    
    return 0;
}