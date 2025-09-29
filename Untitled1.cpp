#include <iostream>
using std::cout;
using std::cin;
using std::endl;

bool simple(int n){
    bool res = true;
    for (int i = 2; i < n - 1; i++){
        if (n % i == 0)
            res = false;
    }
    return res;
}
int main()
{
    int n, current = 0, number = 2;
    cin>>n;
    while (current != n){
        if (simple(number)){
            number ++;
            current ++;
        }
        else{
            number++;
        }
    }
    cout<<number - 1;
}
