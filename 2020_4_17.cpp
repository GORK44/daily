//二叉树的层序遍历
//给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
//
//
//
//示例：
//二叉树：[3,9,20,null,null,15,7],
//
//3
/// \
//9  20
///  \
//15   7
//返回其层次遍历结果：
//
//[
// [3],
// [9,20],
// [15,7]
// ]

#include <iostream>
#include <vector>
#include<unordered_map>
#include<stack>
#include<queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//DFS 深度优先
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        addVector(root,0);      //调用递归函数
        return res;
    }
    
    void addVector(TreeNode* root,int level)
    {
        if(root == NULL)    return;
        if(res.size()==level)       res.resize(level+1);    //level表示层数，也对应二维数组的第一层索引，
        res[level].push_back(root->val);    //当前深度的节点保存到res[level]
        addVector(root->left,level+1);      //递归向下一深度，level+1
        addVector(root->right,level+1);
    }
};

//BFS 广度优先
class Solution1 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        
        if (root == NULL)   return {};
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty())
        {
            vector<int>level;                //存放每一层的元素值
            int count=q.size();             //队列大小表示当前层数的元素个数
            while(count--)                  //count--逐个对该层元素进行处理
            {
                TreeNode *t=q.front();             q.pop();
                level.push_back(t->val);
                if(t->left)     q.push(t->left);
                if(t->right)    q.push(t->right);
            }
            
            res.push_back(level);           //将当层元素的vector加入res中
        }
        return res;
    }
};
