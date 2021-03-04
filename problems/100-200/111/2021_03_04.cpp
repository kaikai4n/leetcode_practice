/**
 * https://leetcode.com/problems/minimum-depth-of-binary-tree/
 * Breadth first search
 * Runtime: 208 ms, faster than 98.23% of C++ online submissions
 * Memory Usage: 144.7 MB, less than 52.21% of C++ online submissions
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 1;
        while (!q.empty()) {
            int qSize = q.size();
            for (int i = 0; i < qSize; i ++) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left == nullptr && node->right == nullptr)
                    return depth;
                if (node->left != nullptr)
                    q.push(node->left);
                if (node->right != nullptr)
                    q.push(node->right);
            }
            depth ++;
        }
        return depth;
    }
};
