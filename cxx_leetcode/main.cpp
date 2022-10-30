#include <iostream>
#include <vector>
#include<math.h>
#include<map>
#include<algorithm>
using namespace std;
#include"Solution.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    ListNode x(10);
    x.next=new ListNode(11);
    x.next->next=new ListNode(12);
    x.next->next->next =new ListNode(13);
    Solution solution=Solution();
    ListNode *ret;
    ret=solution.swapPairs(&x);
}

