#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/*В круг выстроено N человек, пронумерованных числами от 1 до N.
Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й,
затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом,
уцелеет 4-й.
Необходимо определить номер уцелевшего. */

struct person_number {
    int number;
    person_number *next;
};

person_number* circle_of_person (int const &count) {
    if (count ==0) return nullptr;
    auto *first = new (person_number);
    first->number=1;
    first->next= nullptr;
    person_number *current;
    for(int i=0; i<count-1; i++){
        if (i==0) {
            first->next = new (person_number);
            current = first->next;
        }
        else {
            current->next = new (person_number);
            current=current->next;
        }
        current->number=i+2;
        current->next= nullptr;
    }
    current->next=first;
    return first;
}

person_number* logic(person_number *first, int const &number_loser, int &winer){
    if (first==nullptr) return nullptr;
    if (number_loser==0) return nullptr;
    person_number *current = first->next;
    int i=1;
    while (current->next->next != current){
        i++;
        if (i==number_loser){
            i=0;
            first->next=current->next;
            delete current;

        } else first=first->next;
        current=first->next;
    }
    winer=number_loser%2==0?current->number:current->next->number;
    return first;
}

void clear (person_number *first) {
    if (first==nullptr) return;
    delete first->next;
    delete first;
}

int main() {
    int count;
    int number_loser;
    cin >> count;
    cin >> number_loser;
    person_number *first=circle_of_person(count);
    int winer=0;
    first=logic(first, number_loser, winer);
    cout<<winer<<endl;
    clear(first);
    return 0;
}
