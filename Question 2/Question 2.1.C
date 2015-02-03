#include <iostream>
#include <fstream>

using namespace std;

const int SIZE = 10000;
int integer_array[SIZE];

int quicksort(int left, int right);
int partition(int left, int right);

int main()
{
    ifstream fin("QuickSort.txt");
    
    for (int i = 0; i < SIZE; ++i) {
        fin >> integer_array[i];
    }
    fin.close();
    
    cout << quicksort(0, SIZE) << endl;
    
    return 0;
}

int quicksort(int left, int right)
{
    if (right - left <= 1) {
        return 0;
    }
    
    int pivot(partition(left, right));
    return right - left - 1 + quicksort(left, pivot) + quicksort(pivot + 1, right);
}

int partition(int left, int right)
{
    int temp;
    int pivot(integer_array[left]);
    int i(left);
    for (int j = left + 1; j < right; ++j) {
        if (integer_array[j] < pivot) {
            temp = integer_array[++i];
            integer_array[i] = integer_array[j];
            integer_array[j] = temp;
        }
    }
    integer_array[left] = integer_array[i];
    integer_array[i] = pivot;
    return i;
}