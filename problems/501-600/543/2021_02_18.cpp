/*
 * https://leetcode.com/problems/diameter-of-binary-tree/
 * time: O(n), space: O(n)
 * Runtime: 4 ms, faster than 97.30% of C++ online submissions
 * Memory Usage: 20.2 MB, less than 94.78% of C++ online submissions
*/

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxDepth = 0;
        this->recurDiameter(root, maxDepth);
        return maxDepth;
    }
private:
    int recurDiameter(TreeNode* node, int& maxDepth) {
        if (node == nullptr)
            return 0;
        int lDepth = this->recurDiameter(node->left, maxDepth);
        int rDepth = this->recurDiameter(node->right, maxDepth);
        maxDepth = max(maxDepth, lDepth + rDepth);
        return max(lDepth, rDepth) + 1;
    }
};
