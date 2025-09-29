#include <iostream>
using std::cin;
using std::cout;
int main(){
    int n;
    cin>>n;
    int digits = 0;
    for(int n_copy = n;n!= 0; n_copy = n_copy >> 1){
        digits++;
    }
    int mask = 1 << (digits - 1);
    for (;mask != 0;mask = mask >> 1){
        cout<<((mask & n) != 0);
    }

    return 0;
}
