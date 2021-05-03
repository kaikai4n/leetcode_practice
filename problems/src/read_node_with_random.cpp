#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


void printNodeWithRandom(string VarName, auto head) {
    cout << VarName << " = [";
    bool outer = false;
    while (head != NULL) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "(" << head->val << ", ";
        if (head->random == nullptr)
            cout << "null)";
        else
            cout << head->random->val << ")";
        head = head->next;
    }
    cout << "]" << endl;
}


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    Node *head = NULL, *tmpHead = head;
    string delim("],");
    string innerDelim(",");
    auto idx = input.find(delim);
    vector<int> nexts;  // the temporary records of the next pointer
    unordered_map<int, Node*> m;
    int cnt = 0;
    while (idx != string::npos) {
        string thisInput(input.substr(0, idx));
        thisInput = thisInput.substr(1, thisInput.length() - 1);
        // handle value of the node
        auto innerIdx = thisInput.find(innerDelim);
        int val = stoi(thisInput.substr(0, innerIdx));
        if (head == NULL) {
            head = new Node(val);
            tmpHead = head;
        } else {
            tmpHead->next = new Node(val);
            tmpHead = tmpHead->next;
        }
        m[cnt ++] = tmpHead;
        // handle next of the node
        thisInput = thisInput.substr(innerIdx + innerDelim.length());
        int next = (thisInput == "null") ? -1 : stoi(thisInput);
        nexts.push_back(next);
        input = input.substr(idx + delim.length());
        idx = input.find(delim);
    }
    if (input.length() > 0) {
        input = input.substr(1, input.length() - 2);
        auto innerIdx = input.find(innerDelim);
        int val = stoi(input.substr(0, innerIdx));
        input = input.substr(innerIdx + innerDelim.length());
        int next = (input == "null") ? -1 : stoi(input);
        if (head == NULL) {
            head = new Node(val);
            tmpHead = head;
        } else {
            tmpHead->next = new Node(val);
            tmpHead = tmpHead->next;
        }
        m[cnt ++] = tmpHead;
        nexts.push_back(next);
    }
    // handle next
    tmpHead = head;
    cnt = 0;
    while (tmpHead != nullptr) {
        if (nexts[cnt] != -1)
            tmpHead->random = m[nexts[cnt]];
        cnt ++;
        tmpHead = tmpHead->next;
    }
    printNodeWithRandom("input", head);
}
