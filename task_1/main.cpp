#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct person_number {
    int number;
    person_number *next;
};

void input (int &count, int &number_loser) {
    cout << "Enter the number of people:  ";
    cin >> count;
    cout << endl << "Enter the number of the dropout:  ";
    cin >> number_loser;
    cout << endl;
}

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
    input(count, number_loser);
    person_number *first=circle_of_person(count);
    int winer=0;
    first=logic(first, number_loser, winer);
    cout<<"Winner:  "<<winer<<endl;
    clear(first);
    return 0;
}
