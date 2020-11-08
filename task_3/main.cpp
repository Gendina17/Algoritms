#include <iostream>
#include <cassert>
#include <string.h>

/*Реализовать очередь с помощью двух стеков. Использовать стек,
реализованный с помощью динамического буфера.*/

template <class T>
class Stack{
private:
    int current_size;
    int length;
    T *mass;
public:
    virtual ~Stack() {
        delete [] mass;

    }

    explicit Stack(int length):length(length) {
        current_size=0;
        mass = new T[length];
    }
    Stack(const Stack &q)=delete;
    Stack& operator = (const Stack &q) = delete;

    void push_back(const T &element);
    T pop_back();
};

template <class T>
void Stack<T>::push_back(const T& element) {
    if (current_size==length){
        length*=4;
        int *help_mass = new T[length];
        memcpy (help_mass, mass, current_size);
        mass=help_mass;
        delete [] help_mass;
    }
    mass[current_size]=element;
    current_size++;
}

template <class T>
T Stack<T>::pop_back() {
    if (current_size==0)
        return -1;
    current_size--;
    return mass[current_size];
}

template <class T>
class Queue{
private:
    Stack<T> *s1;
    Stack<T> *s2;
public:
    virtual ~Queue() {
        delete s1;
        delete s2;
    }

    Queue(int count) {
        s1 = new Stack<T>(count);
        s2 = new Stack<T>(count);
    }
    Queue(const Queue &q)=delete;
    Queue& operator = (const Queue &q) = delete;
    void push_back(const T &element);
    T pop_front();
};

template <class T>
void Queue<T>::push_back(const T &element) {
    s1->push_back(element);
}

template <class T>
T Queue<T>::pop_front() {
    T element;
    if ((element=s2->pop_back()) != -1)
        return element;
    else
    {
        while ((element=s1->pop_back()) != -1) {
            s2->push_back(element);
        }
    }
    return s2->pop_back();
}

void run (std::istream &input, std::ostream &output){
    int count=0;
    input>>count;
    Queue<int> queue(count);
    bool result= true;
    for(int i=0; i<count; i++){
        int command=0;
        int value=0;
        input>>command>>value;
        switch (command) {
            case 2:
                result=queue.pop_front()==value;
                break;
            case 3:
                queue.push_back(value);
                break;
            default:
                assert(false);
        }
    }
    output<<(result?"YES":"NO");
}

int main() {
    run(std::cin, std::cout);
    return 0;
}