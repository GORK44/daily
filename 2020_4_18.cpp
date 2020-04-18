//合并两个有序链表
//将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
//
//示例：
//
//输入：1->2->4, 1->3->4
//输出：1->1->2->3->4->4

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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        else if (l2 == NULL) return l1;
        else if (l1->val < l2->val) {               //l1<l2
            l1->next = mergeTwoLists(l1->next, l2); //递归
            return l1;                              //返回l1（小的）
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
