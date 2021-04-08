/*
 * https://leetcode.com/problems/binary-tree-preorder-traversal/
 * Runtime: 4 ms, faster than 45.77% of C++ online submissions
 * Memory Usage: 8.4 MB, less than 72.28% of C++ online submissions
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode *node = s.top();
            s.pop();
            if (node != nullptr) {
                res.push_back(node->val);
                s.push(node->right);
                s.push(node->left);
            }
        } 
        return res;
    }
};
