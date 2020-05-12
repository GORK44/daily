//面试题27. 二叉树的镜像
//请完成一个函数，输入一个二叉树，该函数输出它的镜像。
//
//例如输入：
//
//4
///   \
//2     7
/// \   / \
//1   3 6   9
//镜像输出：
//
//4
///   \
//7     2
/// \   / \
//9   6 3   1
//
//
//
//示例 1：
//
//输入：root = [4,2,7,1,3,6,9]
//输出：[4,7,2,9,6,3,1]

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
    TreeNode* mirrorTree(TreeNode* root) {
        if(root == NULL){   //递归返回条件：当前结点为 NULL
            return NULL;
        }
        
        //模型：二叉树的先序遍历（遍历二叉树的所有结点）
        TreeNode* tmp = root->left;//二叉树的镜像就是交换原二叉树中所有结点的左子树和右子树
        root->left = root->right;
        root->right = tmp;
        
        mirrorTree(root->left);
        mirrorTree(root->right);
        
        return root;
    }
};
