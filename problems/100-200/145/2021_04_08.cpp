class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {

    }
    vector<int> postorderTraversalRecursiveMethod(TreeNode* root) {
        /*
         * Runtime: 0 ms, faster than 100.00% of C++ online submissions
         * Memory Usage: 8.6 MB, less than 28.93% of C++ online submissions
        */
        vector<int> res;
        postorderTraversalRecur(root, res);
        return res;
    }
    void postorderTraversalRecur(TreeNode* node, vector<int> &res) {
        if (node == nullptr)
            return;
        postorderTraversalRecur(node->left, res);
        postorderTraversalRecur(node->right, res);
        res.push_back(node->val);
    }
};
