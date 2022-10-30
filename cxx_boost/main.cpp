#include <iostream>
#include<boost/version.hpp>
#include<future>
#include<thread>
using namespace std;
int thread_func();
int main() {
    std::cout << "Hello, World!" << std::endl;
    ::cout<<BOOST_VERSION<<::endl;
    std::future<int> result = std::async(std::launch::async,thread_func);
    auto status = result.wait_for(chrono::microseconds(1000));
    while(1){
        if(status==std::future_status::ready){
            ::cout<<"Future is ready";
        }else{
            ::cout<<"Future is not ready";
        }
        if(status==std::future_status::timeout) break;
    }
    int get = result.get();
    result.wait();
    return 0;
}
int thread_func(){
    std::cout<<"func_thread_start"<<::endl;
    std::this_thread::sleep_for(chrono::seconds(5));
    std::cout<<"func_thread_end"<<std::endl;
    return 100;
}