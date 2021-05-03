#include <iostream>
#include <string>
#include <vector>

using namespace std;



class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


void inorderBSTNode(Node* head, int& leftWidth, int depth, vector<pair<vector<int>, Node*>>& nodes, bool printNext) {
    const int blankWidth = 1, nullWidth = 1;
    if (head == nullptr) {
        nodes.push_back(make_pair(vector<int>{depth, leftWidth, nullWidth}, head));
        leftWidth += (nullWidth + blankWidth);
        return;
    }
    inorderBSTNode(head->left, leftWidth, depth + 1, nodes, printNext);
    int width = 1;
    Node* tmpPrintNode = printNext ? head->next : head;
    if (tmpPrintNode != nullptr) {
        int val = tmpPrintNode->val;
        if (val < 0) {
            val = -val;
            width ++;
        }
        while (val >= 10) {
            val /= 10;
            width ++;
        }
    }
    nodes.push_back(make_pair(vector<int>{depth, leftWidth, width}, tmpPrintNode));
    leftWidth += (width + blankWidth);
    inorderBSTNode(head->right, leftWidth, depth + 1, nodes, printNext);
}


void printBSTNode(string name, Node* head, bool printNext) {
    cout << name << ": " << endl;
    vector<pair<vector<int>, Node*>> nodes;  // pair<vector<int>{depth, left width, current width}, node pointer>
    int leftWidth = 0;
    inorderBSTNode(head, leftWidth, 0, nodes, printNext);
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
    Node* root = (inputVec[0] == "null") ? nullptr : new Node(stoi(inputVec[0]));
    for(int i = 1; i < inputVec.size(); i ++) {
        if (inputVec[i] == "null")
            continue;
        vector<int> dirs;
        int line = i + 1;
        while (line != 1) {
            dirs.push_back(line);
            line /= 2;
        }
        Node* head = root;
        for (auto it = dirs.rbegin(); (it + 1) != dirs.rend(); it ++)
            head = (*it % 2 == 1) ? head->right : head->left;
        if (dirs[0] % 2 == 1)
            head->right = new Node(stoi(inputVec[i]));
        else
            head->left = new Node(stoi(inputVec[i]));
    }
    printBSTNode("input", root, false);
    printBSTNode("next of input", root, true);
}
