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
    int n=0;
    int res;
    int kthSmallest(TreeNode* root, int k) {
        //递归
        dfs(root,k);
        return res;
    }
    
    void dfs(TreeNode* root,int k){
        if(!root)return ;
        
        dfs(root->left,k);  //先left后right，二叉搜索树中序遍历从小到大
        n++;
        if(n==k) res=root->val;
        dfs(root->right,k);
    }
    
};
