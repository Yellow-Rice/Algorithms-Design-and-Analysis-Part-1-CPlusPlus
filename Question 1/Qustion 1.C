#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

const int SIZE = 100000;
int integer_array[SIZE];
int temp_left_array[SIZE + 1];
int temp_right_array[SIZE + 1];

long long int count_inversions(const int start, const int end);
long long int count_split_inversions(const int start, const int mid, const int end);

int main()
{
    ifstream fin("IntegerArray.txt");
    
    for (int i = 0; i < SIZE; ++i) {
        fin >> integer_array[i];
    }
    fin.close();
    
    cout << count_inversions( 0, SIZE) << endl;
    
    return 0;
}

long long int count_inversions(const int start, const int end)
{
    if (end - start <= 1) {
        return 0;
    }
    int mid((start + end) / 2);
    return count_inversions(start, mid) + count_inversions(mid, end) + count_split_inversions(start, mid, end);
}

long long int count_split_inversions(const int start, const int mid, const int end)
{
    long long int counter(0);
    
    for (int i = start; i < mid; ++i) {
        temp_left_array[i] = integer_array[i];
    }
    temp_left_array[mid] = INT_MAX;
    for (int j = mid; j < end; ++j) {
        temp_right_array[j] = integer_array[j];
    }
    temp_right_array[end] = INT_MAX;
    
    for (int i = start, j = mid, k = start; k < end; ++k) {
        if (temp_left_array[i] <= temp_right_array[j]) {
            integer_array[k] = temp_left_array[i++];
        }
        else {
            integer_array[k] = temp_right_array[j++];
            counter += mid - i;
        }
    }
    
    return counter;
}
