#include <algorithm>
#include <cassert>
#include <iostream>

/*Для сложения чисел используется старый компьютер. 
Время, затрачиваемое на нахождение суммы двух чисел равно их сумме. 
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время,
в зависимости от порядка вычислений. 
((1+2)+3) -> 1+2 + 3+3 = 9 
((1+3)+2) -> 1+3 + 4+2 = 10
((2+3)+1) -> 2+3 + 5+1 = 11
Требуется написать программу, которая определяет минимальное время, 
достаточное для вычисления суммы заданного набора чисел. */

template<class T>
class Heap {
public:
    Heap(T *arr, int size);
    ~Heap();
    void Insert(T element);
    T get_min();
    bool IsEmpty();
    Heap& operator= (const Heap<T>& _arr)=default;
    Heap(const Heap<T>& _arr)=default;
private:
    void buildHeap();
    void siftDown(int i);
    void siftUp( int i );
    void add(T element);
    T *array;
    int current_size = 0;
    int size = 0;
};

template<class T>
void Heap<T>::buildHeap() {
    for (int i = size / 2 - 1; i >= 0; --i) {
        siftDown(i);
    }
}

template<class T>
void Heap<T>::add(T element) {
    if (current_size >= size) {
        T *array_help = new T[size * 2];
        for (int i = 0; i < size; i++) {
            array_help[i] = array[i];
        }
        delete [] array;
        array = array_help;
        size *= 2;
    }
    array[current_size] = element;
}

template<class T>
Heap<T>::Heap(T *arr, int size) {
    assert(array != nullptr);
    this->size = size;
    current_size = 0;
    array = new T[size];
    for (int i = 0; i < size; i++) {
        add(arr[i]);
        current_size++;
    }
    buildHeap();
}

template<class T>
Heap<T>::~Heap() {
    delete [] array;
}

template<class T>
void Heap<T>::siftDown(int i)  {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int smallest = i;

    if (left < current_size && array[left] < array[smallest]) {
        smallest = left;
    }
    if (right < current_size && array[right] < array[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        std::swap(array[i], array[smallest]);
        siftDown(smallest);
    }
}

template<class T>
void Heap<T>::siftUp(int i) {
    while (i > 0) {
        int parent = (i - 1)/ 2;

        if (array[i]> array[parent]) {
            return;
        }
        std::swap(array[i], array[parent]);
        i = parent;
    }
}

template<class T>
T Heap<T>::get_min() {
    assert(current_size != 0);
    T save_min = array[0];
    if (current_size == 1) {
        current_size--;
        return save_min;
    }
    current_size--;
    array[0] = array[current_size];
    siftDown(0);

    return save_min;
}

template<class T>
void Heap<T>::Insert(T element) {
    add(element);
    siftUp(current_size);
    current_size++;
}

template<class T>
bool Heap<T>::IsEmpty() {
    if (current_size == 0) {
        return true;
    }
    return false;
}

int quick_addition(Heap<int> &heap) {
    int result = 0;
    int min1;
    int min2;
    while (true) {
        min1 = heap.get_min();
        min2 = heap.get_min();
        result += min1 + min2;

        if (heap.IsEmpty()) {
            return result;
        } else {
            heap.Insert(min1 + min2);
        }
    }
}

int main() {
    int count = 0;
    assert(std::cin >> count);
    int *array = new int[count];
    for (int i = 0; i < count; ++i) {
        std::cin >> array[i];
    }
    Heap<int> heap(array, count);
    delete [] array;
    std::cout << quick_addition(heap);
    return 0;
}