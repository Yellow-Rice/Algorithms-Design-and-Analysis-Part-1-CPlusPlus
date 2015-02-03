#include <iostream>
#include <fstream>
using namespace std;

long long int count_inversions(const int integer_array[], const int SIZE);

int main()
{
    ifstream fin("IntegerArray.txt");
    const int SIZE = 100000;
    int integer_array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        fin >> integer_array[i];
    }
    fin.close();
    
    cout << count_inversions(integer_array, SIZE) << endl;
    
    return 0;
}

long long int count_inversions(const int integer_array[], const int SIZE)
{
    long long int counter(0);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = i + 1; j < SIZE; ++j) {
            if (integer_array[i] > integer_array[j]) {
                ++counter;
            }
        }
    }
    return counter;
}
