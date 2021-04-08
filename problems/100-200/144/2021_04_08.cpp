/*
 * https://leetcode.com/problems/binary-tree-preorder-traversal/
 */
class Solution {
public:
    vector<int> preorderTraversalMorris(TreeNode* root) {
        /*
         * Morris like traversal.
         * time: O(n), space: O(1)
         * Runtime: 4 ms, faster than 45.77% of C++ online submissions
         * Memory Usage: 8.3 MB, less than 72.28% of C++ online submissions
        */
        vector<int> res;
        while (root != nullptr) {
            res.push_back(root->val);
            if (root->left == nullptr) {
                root = root->right;
            } else if (root->right == nullptr) {
                root = root->left;
            } else {
                // both left and right are not null
                TreeNode* node = root->left;
                while (node->right != nullptr)
                    node = node->right;
                node->right = root->right;
                root->right = nullptr;
                root = root->left;
            }
        }
        return res;
    }
    vector<int> preorderTraversalRecursive(TreeNode* root) {
        /*
         * time: O(n), space: O(n)
         * Runtime: 4 ms, faster than 45.77% of C++ online submissions
         * Memory Usage: 8.4 MB, less than 72.28% of C++ online submissions
        */
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
