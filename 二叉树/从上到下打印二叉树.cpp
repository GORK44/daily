//面试题32 - I. 从上到下打印二叉树
//从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
//
//
//
//例如:
//给定二叉树: [3,9,20,null,null,15,7],
//
//3
/// \
//9  20
///  \
//15   7
//返回：
//
//[3,9,20,15,7]

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> res;  //用来保存输出结果
        if(!root) return res; //如果二叉树空，返回
        
        queue<TreeNode*> que; //队列（BFS广度优先保存每一层）
        que.push(root); //保存root到队列
        //queue只能访问第一个和最后一个元素。只能在容器的末尾添加新元素，只能从头部移除元素。
        
        TreeNode* temp;
        while (!que.empty()) {  //若队列不空，证明当前层还有元素
            temp = que.front(); //保存que第一个元素
            que.pop();          //删除第一个元素
            res.push_back(temp->val); //保存当前节点值（队列第一个值）到res数组
            if(temp->left) que.push(temp->left);   //保存左右子节点到队列
            if(temp->right) que.push(temp->right);
        }
        
        return res;
    }
};
