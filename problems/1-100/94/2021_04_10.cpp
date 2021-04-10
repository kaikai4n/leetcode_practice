/*
 * https://leetcode.com/problems/binary-tree-inorder-traversal/
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        /*
         * Morris Traversal: time: O(n), sapce: O(1)
         *      Each node is at most traveled three times:
         *          1. the right leaf traversal by the upper level node
         *          2. when p1 is this node
         *          3. when p1 is traversed again when left leaves are traversed.
         * Runtime: 4 ms, faster than 45.43% of C++ online submissions
         * Memory Usage: 8.4 MB, less than 56.87% of C++ online submissions
        */
        vector<int> res;
        TreeNode *p1 = root, *p2 = nullptr;
        while (p1 != nullptr) {
            p2 = p1->left;
            if (p2 != nullptr) {
                while (p2->right != nullptr && p2->right != p1)
                    p2 = p2->right;
                if (p2->right == nullptr) {
                    p2->right = p1;
                    p1 = p1->left;
                } else {
                    p2->right = nullptr;
                    res.push_back(p1->val);
                    p1 = p1->right;
                }
            } else {
                res.push_back(p1->val);
                p1 = p1->right;         
            }
        }
        return res;
    }
    vector<int> inorderTraversalStack(TreeNode* root) {
        /*
         * time: O(n), space: O(n)
         * Runtime: 8 ms, faster than 45.43% of C++ online submissions
         * Memory Usage: 8.3 MB, less than 56.87% of C++ online submissions
        */
        stack<TreeNode*> s;
        vector<int> res;
        while (root != NULL || !s.empty()){
            while (root != NULL) {
                s.push(root);
                root = root->left;
            }
            root = s.top(); s.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};
