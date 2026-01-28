#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<char> a= {'h', 'e', 'l', 'l', 'o'};
    int n=0;
    for(int i=a.size()-1;i>=0;i--){
        a.at(n) = a.at(i);
        n++;
    }
    return 0;
}