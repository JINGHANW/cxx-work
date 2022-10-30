//
// Created by wjh on 2022/1/14.
//

#include "Solution.h"
#include<vector>
#include<map>
using namespace std;

ListNode *Solution::swapPairs(ListNode *head) {
    vector<ListNode *> ptr_vec;
    ListNode *first = head;
    ListNode *ret;
    int size=0;
    if(head->next== nullptr){
        return head;
    }else if(head== nullptr){

        return nullptr;
    }
    while(first!= nullptr){
        ptr_vec.push_back(first);
        first=first->next;
        size++;
    }
    int count=size;
    ListNode *current_next=ptr_vec[1];
    for(int i=0;i<count;i++){
        if(i==count-1){
            current_next->next=nullptr;
            break;
        }
        if(i%2==0){
            current_next->next=ptr_vec[i];
        }else if(i%2==1){
            current_next->next=ptr_vec[i+2];
        }
        current_next=current_next->next;
    }
    return ptr_vec[1];
}


