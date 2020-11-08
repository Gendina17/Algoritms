#include <iostream>
#include <cstring>
#include <assert.h>

#define SIZE 256
#define BYTE_COUNT 8

/*Дан массив неотрицательных целых 64-битных чисел.
Количество чисел не больше 1000000.
Отсортировать массив методом поразрядной сортировки LSD по байтам.*/

int getDigit(long long value, int digit){
    return (value >> 8 * digit ) & 255;
}

void CountingSort( long long* a, int n, int digit ) {
    int k=SIZE;
    int* c = new int[k];
    for( int i = 0; i < k; ++i )
        c[i] = 0;
    for( int i = 0; i < n; ++i )
        ++c[getDigit(a[i], digit)];
    int sum = 0;
    for( int i = 0; i < k; ++i ) {
        int tmp = c[i];
        c[i] = sum;
        sum += tmp;
    }
    long long* b = new long long [n];
    for( int i = 0; i < n; ++i ) {
        b[c[getDigit(a[i], digit)]++] = a[i];
    }
    delete[] c;
    memcpy( a, b, n * sizeof( long long ) );
    delete[] b;
}
int main() {
    int count = 0;
    assert(std::cin >> count);
    long long *mas = new long long [count];
    for (size_t i = 0; i < count; i++) {
        std::cin >> mas[i];
    }
    for(int i=0; i<BYTE_COUNT;i++){
        CountingSort(mas, count, i);
    }
    for (int i = 0; i < count; i++) {
        std::cout << mas[i] << " ";
    }
    delete [] mas;
    return 0;
}
