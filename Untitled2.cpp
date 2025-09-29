#include <iostream>
int main()
{
    int n;
    std::cin>>n;
    for (int i = 1; i < n + 1; i ++){
        if(n % i == 0){
            std::cout<<i<<" ";
        }
    }
}
