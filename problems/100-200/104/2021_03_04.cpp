/**
 * https://leetcode.com/problems/maximum-depth-of-binary-tree/
 * Runtime: 8 ms, faster than 80.50% of C++ online submissions
 * Memory Usage: 18.7 MB, less than 92.86% of C++ online submissions
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
