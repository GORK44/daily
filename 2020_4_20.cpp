//反转链表
//反转一个单链表。
//
//示例:
//
//输入: 1->2->3->4->5->NULL
//输出: 5->4->3->2->1->NULL

#include <iostream>
#include <vector>
#include<unordered_map>
#include<stack>
#include<queue>
using namespace std;


//单链列表的定义。 Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = NULL, *pre = head;  //前后两个指针
        while (pre != NULL) {
            ListNode* t = pre->next;    //保存pre->next
            pre->next = cur;    //前面节点的next指向当前节点
            cur = pre;      //cur前进，指向pre指向节点
            pre = t;    //pre前进，指向下一个节点
        }
        return cur;
    }
};
