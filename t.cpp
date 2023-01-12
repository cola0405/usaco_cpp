#include <iostream>
#include <string>
using namespace std;
int main() {
    long long k = 1000000000;
    long long x = 14339;
    cout<<2*k<<endl;
    cout<<x*x<<endl;
    int s = (2*k + x*x - x) / 2;
    cout<<s<<endl;
}