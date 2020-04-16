//二叉搜索树的最近公共祖先
//给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
//
//百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
//
//例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]
//
//
//示例 1:
//
//输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
//输出: 6
//解释: 节点 2 和节点 8 的最近公共祖先是 6。

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


//思路：此题其实是一道先序遍历的特性题，但是由于树被限定为了 二叉搜索树，此题就变得很简单了。因为由于二叉搜索树具有很强的特性，每个节点的右孩子均大于左孩子，所以我们要找他们最先出现的祖先节点，这意味着他们一定在某一个节点的两边，对于这个节点就是他们最先出现的祖先节点，此节点满足二叉搜索树种的特点，只需要找到某个节点中同时满足大于p节点的值还满足小于q节点的值即可（因为题目规定p<q）


class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL) return NULL;
        if(root->val>p->val&&root->val<q->val) return root; //比节点p的值大，比节点q的值小，返回当前节点。
        if(root->val>p->val&&root->val>q->val) return lowestCommonAncestor(root->left,p,q);//当前节点比两个节点都大，向左递归。
        if(root->val<p->val&&root->val<q->val) return lowestCommonAncestor(root->right,p,q);//当前节点比两个节点都小，向右递归。
        return root;
    }
};
