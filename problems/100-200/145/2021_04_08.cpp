/*
 * https://leetcode.com/problems/binary-tree-postorder-traversal/
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
    void addPath(TreeNode *n, vector<int> &res) {
        int cnt = 0;
        while (n != nullptr) {
            res.push_back(n->val);
            n = n->right;
            cnt ++;
        }
        int l = res.size() - cnt, r = res.size() - 1;
        while (r > l)
            swap(res[l ++], res[r --]);
    }
    vector<int> postorderTraversalMorris(TreeNode* root) {
        /*
         * Morris Algorithm: time: O(n), space: O(1)
         * Each node is at most traversed 6 times. For example, for "2" in
         *         1
         *     2       3
         *   4   5   6   7
         * 1. "2" is firstly traversed by "1" to connect "5" to "1".
         * 2. "2" is assigned as the root node "p1" and connected from "4"
         *    to "2".
         * 3. After "4" is processed, "p1" is again assign to "2" and the
         *    loop is detected and freed. "p1" is then assigned as "5" in
         *    the next round.
         * 4. When "1" is assigned as "p1" again, the loop of "5" to "1" is
         *    detected by traversing "2" to "5" to "1".
         * 5. Add the reversed result in results with "2" and "5".
         * 6. Reverse the result to "5" and "2".
         * Runtime: 0 ms, faster than 100.00% of C++ online submissions
         * Memory Usage: 8.3 MB, less than 93.22% of C++ online submissions
        */
        vector<int> res;
        TreeNode *p1 = root, *p2 = nullptr;
        while (p1 != nullptr) {
            p2 = p1->left;
            if (p2 == nullptr) {
                p1 = p1->right;
            } else {
                while (p2->right != nullptr && p2->right != p1)
                    p2 = p2->right;
                if (p2->right == nullptr) {
                    p2->right = p1;
                    p1 = p1->left;
                } else {
                    p2->right = nullptr;
                    addPath(p1->left, res);
                    p1 = p1->right;
                }
            }
        }
        addPath(root, res);
        return res;
    }
    vector<int> postorderTraversalRecursiveMethod(TreeNode* root) {
        /*
         * Recursive traversal:
         * time: O(n), space: O(n)
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
