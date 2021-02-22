/*
 * https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
 * Using inorder traverse to simulate the path
 * time: O(n), space: O(log(n))
 * runtime: 32 ms, memory: 31.1 MB
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


void printLinkList(string VarName, auto head) {
    cout << VarName << " = [";
    bool outer = false;
    while (head != NULL) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << head->val;
        head = head->next;
    }
    cout << "]" << endl;
}


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
    TreeNode* sortedListToBST(ListNode* head) {
        int n = 0;
        ListNode* tmpHead = head;
        while (tmpHead != nullptr) {
            tmpHead = tmpHead->next;
            n ++;
        }
        if (n == 0)
            return nullptr;
        this->moveListHead = head;
        return this->inorderTraverse(0, n - 1);
    }
private:
    ListNode* moveListHead;
    TreeNode* inorderTraverse(int l, int r) {
        if (l == r) {
            TreeNode* treeHead = new TreeNode(moveListHead->val);
            moveListHead = moveListHead->next;
            return treeHead;
        } else if (l > r)
            return nullptr;
        int m = l + (r - l) / 2;
        TreeNode* treeHead = new TreeNode();
        treeHead->left = this->inorderTraverse(l, m - 1);
        treeHead->val = moveListHead->val;
        moveListHead = moveListHead->next;
        treeHead->right = this->inorderTraverse(m + 1, r);
        return treeHead;
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    ListNode *head = NULL, *tmpHead = head;
    string delim(",");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        if (head == NULL) {
            head = new ListNode(stoi(input.substr(0, idx)));
            tmpHead = head;
        } else {
            tmpHead->next = new ListNode(stoi(input.substr(0, idx)));
            tmpHead = tmpHead->next;
        }
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0) {
        if (head == NULL) {
            head = new ListNode(stoi(input));
            tmpHead = head;
        } else
            tmpHead->next = new ListNode(stoi(input));
    }
    printLinkList("input", head);
    Solution sol;
    printBST("solution", sol.sortedListToBST(head));
}
