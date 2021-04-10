/*
 * https://leetcode.com/problems/binary-tree-preorder-traversal/
 */
class Solution {
public:
    vector<int> preorderTraversalMorris(TreeNode* root) {
        /*
         * Morris Algorithm: time: O(n), space: O(1)
         * Runtime: 0 ms, faster than 100.00% of C++ online submissions
         * Memory Usage: 8.4 MB, less than 72.14% of C++ online submissions
        */
        vector<int> res;
        TreeNode *p1 = root, *p2 = nullptr;
        while (p1 != nullptr) {
            p2 = p1->left;
            if (p2 == nullptr) {
                res.push_back(p1->val);
                p1 = p1->right;
            } else {
                while (p2->right != nullptr && p2->right != p1)
                    p2 = p2->right;
                if (p2->right == nullptr) {
                    p2->right = p1;
                    res.push_back(p1->val);
                    p1 = p1->left;
                } else {
                    p2->right = nullptr;
                    p1 = p1->right;
                }
            }
        }
        return res;
    }
    vector<int> preorderTraversalMorrisLike(TreeNode* root) {
        /*
         * A Morris like traversal but modified the tree structure.
         *   1            1
         * 2   3    =>  2
         *               3
         * time: O(n), space: O(1)
         * Runtime: 4 ms, faster than 45.77% of C++ online submissions
         * Memory Usage: 8.3 MB, less than 72.14% of C++ online submissions
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
