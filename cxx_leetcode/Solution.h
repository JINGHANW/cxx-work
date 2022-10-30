//
// Created by wjh on 2022/1/14.
//

#ifndef CXX_LEETCODE_SOLUTION_H
#define CXX_LEETCODE_SOLUTION_H
#include<vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    public:
    ListNode* swapPairs(ListNode* head);
    void setZeroes(vector<vector<int>>& matrix);

    Solution(){};
};


#endif //CXX_LEETCODE_SOLUTION_H
