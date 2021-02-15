/*
 * https://leetcode.com/problems/binary-tree-maximum-path-sum
 * 1. dfs each node
 * 2. For each node, 
 *      (a) If node is null, return minimum possible value
 *      (b) If node is leaf, return the node's val
 *      (c) Traverse left and right leaf nodes and get the 
 *          maximum path sums from them, called lVal and rVal.
 *          Calculate this nodes maximum sum and compares with
 *          the maximum variable maxVal: 
 *              node.val + max(lVal, 0) + max(rVal, 0)
 *      (d) return the single path sum (left or right):
 *          return node.val + max(max(lVal, rVal), 0)
 * time: O(n), space: O(log(n))
 * Runtime: 20 ms, faster than 94.61% of C++ online submissions
 * Memory Usage: 27.6 MB, less than 94.82% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


void inorderBST(TreeNode* head, int& leftWidth, int depth, vector<pair<vector<int>, TreeNode*>>& nodes) {
    const int blankWidth = 1, nullWidth = 1;
    if (head == nullptr) {
        nodes.push_back(make_pair(vector<int>{depth, leftWidth, nullWidth}, head));
        leftWidth += (nullWidth + blankWidth);
        return;
    }
    inorderBST(head->left, leftWidth, depth + 1, nodes);
    int width = 1, val = head->val;
    if (val < 0) {
        val = -val;
        width ++;
    }
    while (val >= 10) {
        val /= 10;
        width ++;
    }
    nodes.push_back(make_pair(vector<int>{depth, leftWidth, width}, head));
    leftWidth += (width + blankWidth);
    inorderBST(head->right, leftWidth, depth + 1, nodes);
}


void printBST(string name, TreeNode* head) {
    cout << name << ": " << endl;
    vector<pair<vector<int>, TreeNode*>> nodes;  // pair<vector<int>{depth, left width, current width}, node pointer>
    int leftWidth = 0;
    inorderBST(head, leftWidth, 0, nodes);
    for (int i = 0, cnt = 0, depth = 0, prevLeftWidth = 0; cnt < nodes.size(); i = (i + 1) % nodes.size()) {
        if (nodes[i].first[0] == depth) {
            cnt ++;
            for (int t = 0; t < nodes[i].first[1] - prevLeftWidth; t ++)
                cout << " ";
            prevLeftWidth = nodes[i].first[1] + nodes[i].first[2];
            if (nodes[i].second == nullptr)
                cout << "n";
            else
                cout << nodes[i].second->val;
        }
        if ((i + 1) / nodes.size() == 1) {
            depth += 1;
            prevLeftWidth = 0;
            cout << endl;
        }
    }
    cout << endl;
}


class Solution {
public:
    const int minMaxVal = -1000;
    int maxPathSum(TreeNode* root) {
        int maxVal = this->minMaxVal;
        this->dfsMaxPathSum(root, maxVal);
        return maxVal;
    }
    int dfsMaxPathSum(TreeNode* head, int& maxVal) {
        if (head == nullptr)
            return minMaxVal;
        if (head->left == nullptr && head->right == nullptr) {
            if (head->val > maxVal)
                maxVal = head->val;
            return head->val;
        }
        int lVal = this->dfsMaxPathSum(head->left, maxVal);
        int rVal = this->dfsMaxPathSum(head->right, maxVal);
        int val = head->val + max(lVal, 0) + max(rVal, 0);
        if (val > maxVal)
            maxVal = val;
        return head->val + max(max(lVal, rVal), 0);
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    vector<string> inputVec;
    string delim(",");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec.push_back(input.substr(0, idx));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec.push_back(input);
    TreeNode* root = (inputVec[0] == "null") ? nullptr : new TreeNode(stoi(inputVec[0]));
    queue<TreeNode*> inputQ;
    inputQ.push(root);
    int vecI = 1;
    while (!inputQ.empty() && vecI < inputVec.size()) {
        int inputQSize = inputQ.size();
        for (int t = 0; t < inputQSize; t ++) {
            TreeNode* node = inputQ.front(); inputQ.pop();
            if (node != nullptr) {
                if (inputVec[vecI] != "null")
                    node->left = new TreeNode(stoi(inputVec[vecI]));
                inputQ.push(node->left);
                vecI ++;
                if (vecI >= inputVec.size())
                    break;
                if (inputVec[vecI] != "null")
                    node->right = new TreeNode(stoi(inputVec[vecI]));
                inputQ.push(node->right);
                vecI ++;
            }
        }
    }
    printBST("input", root);
    Solution sol;
    cout << "solution = " << sol.maxPathSum(root) << endl;
}
