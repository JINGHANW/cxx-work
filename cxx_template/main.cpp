#include <iostream>
#include <map>
using namespace std;

void test(int a, int b =9);
int main() {
    test(1);
    test(1,11);
}
void test(int a,int b){
    cout<<a<<b<<endl;
}
