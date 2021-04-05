/*
 * https://leetcode.com/problems/copy-list-with-random-pointer/
 * Method:
 *      1. Deepcopy val of each node in one pass. When traversing,
 *         record the mapping from the source node to the target 
 *         node of the same corresponding nodes.
 *      2. Traverse again to fill in the random pointer with the
 *         mapping from the first step.
 * time: O(n), space: O(n)
 * Runtime: 8 ms, faster than 73.65% of C++ online submissions
 * Memory Usage: 11.3 MB, less than 70.03% of C++ online submissions
*/

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


class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr)
            return nullptr;
        unordered_map<Node*, Node*> m;
        Node* tmpHeadOri = head->next;
        Node* newHead = new Node(head->val);
        Node* tmpHeadNew = newHead;
        m[head] = newHead;
        int cnt = 1;
        while (tmpHeadOri != nullptr) {
            tmpHeadNew->next = new Node(tmpHeadOri->val);
            m[tmpHeadOri] = tmpHeadNew->next;
            tmpHeadNew = tmpHeadNew->next;
            tmpHeadOri = tmpHeadOri->next;
            cnt ++;
        }
        tmpHeadOri = head;
        tmpHeadNew = newHead;
        while (tmpHeadOri != nullptr) {
            if (tmpHeadOri->random != nullptr)
                tmpHeadNew->random = m[tmpHeadOri->random];
            tmpHeadOri = tmpHeadOri->next;
            tmpHeadNew = tmpHeadNew->next;
        }
        return newHead;
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
    Solution sol;
    printNodeWithRandom("solution", sol.copyRandomList(head));
}
