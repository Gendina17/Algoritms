#include <iostream>

/* Реализуйте стратегию выбора опорного элемента “случайный элемент”.
Функцию Partition реализуйте методом прохода двумя итераторами
от конца массива к началу. */

class Cmp_default{
public:
    bool operator()(const int &l1, const int &l2){return l1<l2;}
};

template <class T, class Compare>
int Partition( T* a, T n,Compare cmp ) {
    if( n <= 1 )
        return 0;
    int y=rand()%n;
    std::swap(a[y],a[0]);
    T& pivot = a[0];
    int i = n-1, j = n-1;

    while( j >0 ) {
        for( ;cmp(a[j],pivot); --j ) {}
        if (j>0){
            std::swap( a[i--], a[j--] );
        }
    }
    std::swap( a[i], a[0] );
    return i;
}

template <class T>
T k_statistics( T* a, int n, int k ) {
    int i = Partition( a, n, Cmp_default() );
    while(i != k ) {
        if( k < i )
            n = i;
        else {
            i++;
            a += i;
            n -= i;
            k -= i;
        }
        i = Partition( a, n, Cmp_default() );
    }
    return a[k];
}

int main() {
    int n,k;
    std::cin>>n;
    std::cin>>k;
    int *array=(int*)calloc(n,sizeof(int));
    for(int i=0;i<n;i++){
        std::cin>>array[i];
    }
    std::cout<<k_statistics(array,n,k);
    free(array);
    return 0;
}