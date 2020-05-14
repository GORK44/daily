//面试题32 - II. 从上到下打印二叉树 II
//从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。
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
//返回其层次遍历结果：
//
//[
// [3],
// [9,20],
// [15,7]
// ]

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
