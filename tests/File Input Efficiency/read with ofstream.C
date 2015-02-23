#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("test data");
    int i;
    while (fin >> i) {
        continue;
    }
    fin.close();
    
    return 0;
}