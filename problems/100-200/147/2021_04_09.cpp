/*
 * https://leetcode.com/problems/insertion-sort-list/
 * Method: Use a dummy to implement the insertion sort easier.
 * time: O(n^2), space: O(1)
 * Runtime: 48 ms, faster than 42.70% of C++ online submissions
 * Memory Usage: 9.5 MB, less than 96.15% of C++ online submissions
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


class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        // create dummy head
        head = new ListNode(0, head);
        ListNode *prev = head;
        ListNode *curr = head->next;
        while (curr != nullptr) {
            ListNode *next = curr->next;
            ListNode *insertHead = head;
            while (insertHead->next != nullptr && insertHead->next->val < curr->val)
                insertHead = insertHead->next;
            if (insertHead == prev) {
                // no insertion requires
                prev = curr;
                curr = next;
            } else {
                /*
                 *     2     ->   4   ->   3   ->  5
                 * insertHead   prev     curr     next
                */
                curr->next = insertHead->next;
                insertHead->next = curr;
                /*
                 *     2     ->   3   ->   4   ->   ->  5
                 * insertHead   curr     prev          next
                */
                prev->next = next;
                /*
                 *     2     ->   3   ->   4   ->  5
                 * insertHead   curr     prev     next
                */
                curr = next;
                /*
                 *     2     ->   3   ->   4   ->  5
                 * insertHead            prev     curr
                */
            }
        }
        ListNode *retHead = head->next;
        delete head;
        return retHead;
    }
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
    Solution sol;
    ListNode *sortedHead = sol.insertionSortList(head);
    printLinkList("sortedHead", sortedHead);
}
