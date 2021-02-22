/*
 * https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
 * Deque implementation
 * runtime: 4 ms, memory: 12.1 MB
*/

#include <iostream>
#include <string>
#include <vector>
#include <deque>

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


void printVectorOfVector(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "[";
        bool inner = false;
        for (auto ele: input) {
            if (inner)
                cout << ",";
            else
                inner = true;
            cout << ele;
        }
        cout << "]";
    }
    cout << "]" << endl;
}


class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        deque<TreeNode*> d;
        int cnt = 0;
        d.push_back(root);
        while (!d.empty()) {
            vector<int> levelRes;
            if (cnt % 2 == 0) {
                // pop back, push front
                int popSize = d.size();
                for (int t = 0; t < popSize; t ++) {
                    TreeNode* node = d.back();
                    d.pop_back();
                    if (node != nullptr) {
                        levelRes.push_back(node->val);
                        if (node->left != nullptr)
                            d.push_front(node->left);
                        if (node->right != nullptr)
                            d.push_front(node->right);
                    }
                }
            } else {
                // pop front, push back
                int popSize = d.size();
                for (int t = 0; t < popSize; t ++) {
                    TreeNode* node = d.front();
                    d.pop_front();
                    levelRes.push_back(node->val);
                    if (node->right != nullptr)
                        d.push_back(node->right);
                    if (node->left != nullptr)
                        d.push_back(node->left);
                }
            }
            if (levelRes.size() > 0)
                res.push_back(levelRes);
            cnt ++;
        }
        return res;
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
    for(int i = 1; i < inputVec.size(); i ++) {
        if (inputVec[i] == "null")
            continue;
        vector<int> dirs;
        int line = i + 1;
        while (line != 1) {
            dirs.push_back(line);
            line /= 2;
        }
        TreeNode* head = root;
        for (auto it = dirs.rbegin(); (it + 1) != dirs.rend(); it ++)
            head = (*it % 2 == 1) ? head->right : head->left;
        if (dirs[0] % 2 == 1)
            head->right = new TreeNode(stoi(inputVec[i]));
        else
            head->left = new TreeNode(stoi(inputVec[i]));
    }
    printBST("input", root);
    Solution sol;
    vector<vector<int>> res = sol.zigzagLevelOrder(root);
    printVectorOfVector("solution", res);
}
