/*
 * https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
 * The last element of postorder is the tree node, so find the node in
 * inorder with a preprocessed map to perform recursion on the left
 * and right trees by the node index.
 * time: O(nlog(n)), for each node requires O(log(n)) to query with map
 * space: O(n), the red black tree and the stack to perform recursion
 * runtime: Runtime: 4 ms, faster than 99.96% of C++ online submissions
 * Memory Usage: 26.4 MB, less than 68.57% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        map<int, int> m;
        for (int i = 0; i < inorder.size(); i++)
            m[inorder[i]] = i;
        return this->buildTreeLeftRight(inorder, postorder, 0, 0, inorder.size(), m);
    }
    TreeNode* buildTreeLeftRight(vector<int>& inorder, vector<int>& postorder, int inL, int poL, int len, map<int, int>& m) {
        if (len == 0)
            return nullptr;
        else if (len == 1)
            return new TreeNode(inorder[inL]);
        TreeNode* node = new TreeNode(postorder[poL + len - 1]);
        int inM = m[node->val];
        int leftTreeLen = inM - inL;
        node->left = this->buildTreeLeftRight(inorder, postorder, inL, poL, leftTreeLen, m);
        node->right = this->buildTreeLeftRight(inorder, postorder, inM + 1, poL + leftTreeLen, len - leftTreeLen - 1, m);
        return node;
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 3);
    vector<int> inorder = inputToVectorInt(input);
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    vector<int> postorder = inputToVectorInt(input);
    printVectorInt("inorder", inorder);
    printVectorInt("postoder", postorder);
    Solution sol;
    printBST("solution", sol.buildTree(inorder, postorder));
}
