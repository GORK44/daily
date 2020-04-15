//  二叉搜索树中第K小的元素
//给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。
//
//说明：
//你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。
//
//示例 1:
//
//输入: root = [3,1,4,null,2], k = 1
//3
/// \
//1   4
//\
//2
//输出: 1
//示例 2:
//
//输入: root = [5,3,6,2,4,null,null,1], k = 3
//             5
//            / \
//           3   6
//          /     \
//         2       4
//        /
//       1
//输出: 3

#include <iostream>
#include <vector>
#include<unordered_map>
#include<stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



class Solution {
public:
    //深度优先
    void dfs(TreeNode* root,int& res, bool& find, int& i, int k) {
        if (root == NULL || find) return;       // 如果此节点为空或find=true，返回
        dfs(root->left, res, find, i, k);       // 递归
        if (++i == k) {                     //中序遍历从小到大，第 i=1，2，3。。。 小的数
            res = root->val;                //result = 此节点的值
            find = true;                    //找到
            return;
        }
        dfs(root->right, res, find, i, k);      // 递归
    }
    int kthSmallest(TreeNode* root, int k) {    //第k小的数
        bool find = false;
        int res = -1;
        int i = 0;
        dfs(root, res, find, i, k);             //深度优先，中序遍历
        return res;
    }
};
