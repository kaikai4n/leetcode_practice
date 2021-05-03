#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


vector<int> getSubInput(string input) {
    input = input.substr(1, input.length() - 2);
    string delim(",");
    vector<int> out;
    auto idx = input.find(delim);
    while (idx != string::npos) {
        out.push_back(stoi(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        out.push_back(stoi(input));
    return out;
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


Node* constructNodeFromVec(vector<vector<int>> inputVec) {
    if (inputVec.size() == 0)
        return nullptr;
    vector<Node*> nodeVec(inputVec.size());
    for (int i = 0; i < inputVec.size(); i ++)
        nodeVec[i] = new Node(i + 1);
    for (int i = 0; i < inputVec.size(); i ++)
        for (int idx: inputVec[i])
            nodeVec[i]->neighbors.push_back(nodeVec[idx - 1]);
    return nodeVec[0];
}


void printNode(string varName, Node* node) {
    if (node == nullptr) {
        cout << varName << " = []" << endl;
        return;
    }
    vector<Node*> nodeVec;
    stack<Node*> s;
    s.push(node);
    while (!s.empty()) {
        Node* thisNode = s.top(); s.pop();
        while (thisNode->val > nodeVec.size())
            nodeVec.push_back(nullptr);
        if (nodeVec[thisNode->val - 1] == nullptr) {
            nodeVec[thisNode->val - 1] = thisNode;
            for (Node* thisNodeNeighbor: thisNode->neighbors)
                s.push(thisNodeNeighbor);
        }
    }
    cout << varName << " = [";
    bool outer = false;
    for (auto input: nodeVec) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "[";
        bool inner = false;
        for (auto ele: input->neighbors) {
            if (inner)
                cout << ",";
            else
                inner = true;
            cout << ele->val;
        }
        cout << "]";
    }
    cout << "]" << endl;
}


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    vector<vector<int>> inputVec;
    string delim(",[");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec.push_back(getSubInput(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec.push_back(getSubInput(input));
    printVectorOfVector("input vec", inputVec);
    Node* inputNode = constructNodeFromVec(inputVec);
    printNode("input node", inputNode);
}
