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
}
