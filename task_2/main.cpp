#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

void input_array(int *array, int count){
    cout<<"Input array:"<<endl;
    for(int i=0; i<count; i++){
        cin>>array[i];
    }
}

int search_range(const int *array){
    int power=0;
    while (array[(int)pow(2,power)]<array[(int)pow(2,power+1)]){
        power++;
    }
    return power;
}

int bin_search(int *array, int power){
    int i_left=(int)pow(2,power);
    int i_right=(int)pow(2,power+1);
    int i_key=((i_right-i_left)/2)+i_left;
    while (!(array[i_key-1]<array[i_key] && array[i_key+1]<array[i_key])){
        if (array[i_key+1]<array[i_key-1]){
            i_right=i_key-1;
        }
        if (array[i_key+1]>array[i_key-1]){
            i_left=i_key+1;
        }
        i_key=((i_right-i_left)/2)+i_left;
    }
    return i_key;
}

int main() {
    int count;
    cout << "Enter the count of elements:";
    cin >> count;
    int *array= new int[count];
    input_array(array, count);
    cout << bin_search(array,  search_range(array));
    return 0;
}
