#include <iostream>
#include <cstring>
struct line{
    int l;
    int r;
};

class CmpLine{
public:
    bool operator()(const line &l1, const line &l2){return l1.l<l2.l;}
};

template <class T, class Compare>
void Merge (T *a_left, int firstLen, T *a_right, int secondLen, T *c,Compare cmp){
    int i_left=0;
    int i_right=0;
    int i_c=0;
    while (i_left!=firstLen && i_right!=secondLen){
        if (cmp(a_left[i_left],a_right[i_right])){
            c[i_c]=a_left[i_left];
            i_left++;
        } else{
            c[i_c]=a_right[i_right];
            i_right++;
        }
        i_c++;
    }
    if (i_left!=firstLen ) {
        for (; i_left < firstLen; i_left++) {
            c[i_c] = a_left[i_left];
            i_c++;
        }
    } else {
        for (; i_right < secondLen; i_right++) {
            c[i_c] = a_right[i_right];
            i_c++;
        }
    }

}

template <class T>
void MergeSort( T* a, int aLen ) {
    if (aLen <= 1) {
        return;
    }
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort(a, firstLen);
    MergeSort(a + firstLen, secondLen);
    T *c = new T[aLen];
    Merge(a, firstLen, a + firstLen, secondLen, c, CmpLine());
    memcpy(a, c, sizeof(T) * aLen);
    delete[] c;
}
int length_search(line* mass, int massLen ){
    if(massLen==0) return 0;
    int r_current=0;
    int length=0;
    for(int i=0;i<massLen;i++){
        if(mass[i].l<r_current && mass[i].r>r_current){
            length+=mass[i].r-r_current;
            r_current=mass[i].r;
        } else
            if(mass[i].l>=r_current){
                length+=mass[i].r-mass[i].l;
                r_current=mass[i].r;
            }
    }
    return length;
}

int main() {
int count;
std::cout<<"Enter the number of line: ";
std::cin>>count;
line *mass=new line[count];
for(int i=0;i<count;i++ ){
    std::cout<<"Enter the left and right border:  ";
    std::cin>>mass[i].l>>mass[i].r;
}
MergeSort(mass, count);
std::cout<<length_search(mass, count);
delete [] mass;
return 0;
}
