//环形链表
//给定一个链表，判断链表中是否有环。
//
//为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
//
//
//
//示例 1：
//
//输入：head = [3,2,0,-4], pos = 1
//输出：true
//解释：链表中有一个环，其尾部连接到第二个节点。

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
    bool hasCycle(ListNode* head)
    {
        //两个快慢指针位于同意起点head
        ListNode* faster = head ;  //快的指针
        ListNode* slower = head ;  //慢的指针
        
        while (faster != NULL && faster->next != NULL)
        {
            faster = faster->next->next;  //快的指针每次跑两步
            slower = slower->next;  //慢的指针每次跑一步
            if (faster == slower)  //他们在比赛中相遇了
                return true;  //可以断定是环形道，直道不可能相遇
        }
        return false;  //快的指针到终点了，那就是直道，绕圈跑不会有终点
    }
};
