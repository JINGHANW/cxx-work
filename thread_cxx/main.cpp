#include <iostream>
#include <thread>
#include<future>
#include<pthread.h>
#include<condition_variable>
#include<mutex>
using namespace  std;

int download(){
    int j=0;
    for(int i=0;i<10;i++){
        j=j+i;
        cout<<"this run at index "<<i<<endl;
        this_thread::sleep_for(chrono::seconds (1));

    }
    cout<<"function end"<<endl;
    return j;
}

std::mutex mtx;
std::condition_variable cv;
bool ready = false;
void print_function(int id){
    std::unique_lock<std::mutex> lock(mtx);
    while(!ready){
        cv.wait(lock);
    }
    std::cout<<this_thread::get_id()<<"id \t"<<id<<endl;
}
void start(){
    std::unique_lock<std::mutex> lock(mutex);
    ready=true;
    cv.notify_all();
}
int main() {
    std::thread thread[10];
    for(int i=0;i<10;i++){
        thread[i] = std::thread(print_function,i);
    }
    start();
    for(auto & th :thread){
        th.join();
    }
}


