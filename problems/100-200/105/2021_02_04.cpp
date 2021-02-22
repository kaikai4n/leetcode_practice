/*
 * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 * stack implementation
 * time: O(n), space: O(n)
 * runtime: 12 ms, memory: 25.5 MB
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>

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


vector<int> inputToVectorInt(string input) {
    vector<int> inputVec;
    string delim(",");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec.push_back(stoi(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec.push_back(stoi(input));
    return inputVec;
}


void printVectorInt(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << input;
    }
    cout << "]" << endl;
}


class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0)
            return nullptr;
        stack<TreeNode*> s;
        TreeNode* head = new TreeNode(preorder[0]);
        s.push(head);
        int l = 1, r = 0;
        while (!s.empty()) {
            TreeNode* node = s.top();
            if (node->val == inorder[r]) {
                s.pop();
                r ++;
                if ((s.empty() || (!s.empty() && s.top()->val != inorder[r])) && l < preorder.size()) {
                    node->right = new TreeNode(preorder[l]);
                    l ++;
                    s.push(node->right);
                }
            } else {
                node->left = new TreeNode(preorder[l]);
                l ++;
                s.push(node->left);
            }
        }
        return head;
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 3);
    vector<int> preorder = inputToVectorInt(input);
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    vector<int> inorder = inputToVectorInt(input);
    printVectorInt("preorder", preorder);
    printVectorInt("inoder", inorder);
    Solution sol;
    printBST("solution", sol.buildTree(preorder, inorder));
}
