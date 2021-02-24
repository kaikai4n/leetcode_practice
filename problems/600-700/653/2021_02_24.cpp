/*
 * https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
 * Two pointer method:
 *      time: O(n), space: O(log(n)) if the binary tree is balanced
 * Hash table method:
 *      time: O(n), space: O(n)
 */

class Solution {
public:
    bool findTargetTwoPointer(TreeNode* root, int k) {
        /*
         * Method: Use left and right pointer that points to the smaller and
         *      larger nodes. If the sum is k, then return true. Else if the
         *      sum if larger, than move the larger node to smaller one with
         *      dfs approach. Otherwise, move the smaller node to larger one
         *      with dfs approach. The method stops when the two pointers
         *      points to the same node. All nodes are traversed only once.
         * time: O(n), space: O(log(n)) if the binary tree is balanced.
         * Runtime: 32 ms, faster than 95.14% of C++ online submissions
         * Memory Usage: 36.8 MB, less than 74.17% of C++ online submissions
        */
        stack<TreeNode*> ls, rs;
        ls.push(root);
        rs.push(root);
        while (ls.top()->left != nullptr)
            ls.push(ls.top()->left);
        while (rs.top()->right != nullptr)
            rs.push(rs.top()->right);
        while (ls.top()->val != rs.top()->val) {
            int sum = ls.top()->val + rs.top()->val;
            if (sum == k)
                return true;
            if (sum > k) {
                if (rs.top()->left != nullptr) {
                    TreeNode* node = rs.top();
                    rs.pop();
                    rs.push(node->left);
                    while (rs.top()->right != nullptr)
                        rs.push(rs.top()->right);
                } else
                    rs.pop();
            } else {
                if (ls.top()->right != nullptr) {
                    TreeNode* node = ls.top();
                    ls.pop();
                    ls.push(node->right);
                    while (ls.top()->left != nullptr)
                        ls.push(ls.top()->left);
                } else
                    ls.pop();
            }
        }
        return false;
    }
    bool findTargetHashMethod(TreeNode* root, int k) {
        /*
         * Hash table implementation
         * Runtime: 36 ms, faster than 88.72% of C++ online submissions
         * Memory Usage: 39 MB, less than 31.44% of C++ online submissions
        */
        unordered_set<int> s;
        return dfsFindTarget(root, s, k);
    }
    bool dfsFindTarget(TreeNode* node, unordered_set<int>& s, int k) {
        if (node == nullptr)
            return false;
        if (s.find(k - node->val) != s.end())
            return true;
        s.insert(node->val);
        return dfsFindTarget(node->left, s, k) || dfsFindTarget(node->right, s, k);
    }
};
