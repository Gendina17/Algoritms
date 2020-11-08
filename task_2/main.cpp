#include <iostream>

/*Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m]
значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
Найти m за O( log m ) */

using std::cin;
using std::cout;
using std::endl;

int search_range(const int *array,int count){
    int power_right = 1;
    count--;
    while (power_right < count) {
        if (array[power_right]  > array[power_right + 1]) {
            return power_right;
        }

        power_right *= 2;
    }
    return count;
}

int bin_search(int *array, int i_left, int i_right){
    while (i_right - i_left > 1) {
        int i_key =(i_right + i_left) / 2;
        if (i_key != 0) {
            if (array[i_key] > array[i_key - 1]) {
                i_left = i_key;
            } else {
                i_right = i_key;
            }
        }
    }
    if (array[i_left] < array[i_right]) {
        return i_right;
    }
    return i_left;
}

int main() {
    int count;
    cin >> count;
    int *array= new int[count];
    for(int i=0; i<count; i++){
        cin>>array[i];
    }
    int power_right = search_range(array, count);
    cout <<  bin_search(array, power_right / 2, power_right);
    return 0;
}