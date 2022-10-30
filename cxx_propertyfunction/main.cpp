#include <iostream>
#include <string>
using namespace std;
template<class T,T n>
string get_type_name();

int sum(int a,int b);
enum Color{
    Yellow=1,Red=2,Blue=3,
};
template<int N>
struct int_const{
    static constexpr int value =N;
};
template<int Beg,int End,class F>
void static_for(F const& func){
    if constexpr(Beg ==End){
        return ;
    }else{
        func(int_const<Beg>());
        static_for<Beg+1,End>(func);
    }
}
template<class T>
string get_type_name_dynamic(T n){
    string ret;
    static_for<0,3>([&](auto ic){
        constexpr auto i = ic.value;

        if(n == (T)i) ret = get_type_name<T,(T)i>();
    });
}
int main() {
    string s;
     Color a = Blue;
    s = get_type_name_dynamic(a);
    cout<<s<<endl;
    return 0;
}

template<class T,T n>
string get_type_name(){
    string s = __PRETTY_FUNCTION__ ;
    int first_pos = s.find("T = ");
    int second_pos = s.find("]",first_pos);
    return s.substr(first_pos,second_pos-first_pos);
}

