/*
 * https://leetcode.com/problems/reorder-list/
 * Method:
 *      1. Find the link list length
 *      2. Cut to half and reverse the link list of the second half.
 *      3. Merge the first and reversed second half with interleaving
 *         approach.
 * time: O(n), space: O(1)
 * Runtime: 24 ms, faster than 99.85% of C++ online submissions
 * Memory Usage: 17.7 MB, less than 68.66% of C++ online submissions
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
    void reorderList(ListNode* head) {
        int N = 0;
        ListNode *h = head;
        while (h != nullptr) {
            N ++;
            h = h->next;
        }
        if (N < 3)
            return;
        ListNode *t = head;
        int n = 1;
        while (n != (N + 1) / 2) {
            n ++;
            t = t->next;
        }
        /*
         * 1 -> 2 -> 3 -|-> 4 -> 5 -> null
         *           t      tN
         * 1 -> 2 -> 3 -> null 4 -> 5 -> null
         *                     t    tN
         * 1 -> 2 -> 3 -> null 4 <- 5 -> null
         *                     t    tN
         * 1 -> 2 -> 3 -> null 4 <- 5 -> null
         *                          t    tN
        */
        ListNode *tNext = t->next;
        t->next = nullptr;
        t = tNext;
        tNext = tNext->next;
        t->next = nullptr;
        while (tNext != nullptr) {
            ListNode *tNextNext = tNext->next;
            tNext->next = t;
            t = tNext;
            tNext = tNextNext;
        }
        /*
         * 1 -> 2 -> 3 -> null
         * h
         * 5 -> 4 -> null
         * t
         * 1 -> 5 -> 2 -> 3 -> null
         *           h
         * 4 -> null
         * t
         * 1 -> 5 -> 2 -> 4 -> 3 -> null
         *                     h
         * null
         * t
        */
        h = head;
        while (t != nullptr) {
            tNext = t->next;
            ListNode *hNext = h->next;
            h->next = t;
            t->next = hNext;
            t = tNext;
            h = hNext;
        }
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
    sol.reorderList(head);
    printLinkList("solution", head);
}
