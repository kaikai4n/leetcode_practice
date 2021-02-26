/*
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * Method: binary merge the k lists
 * time: O(Klog(K)N), for worst case K lists with equal length N
 *      T(K) = 2T(K / 2) + O(KN)
 *           = 2^xT(K / 2^x) + x O(KN)
 *      let x = log2(K) => K = 2^x
 *      T(K) = K + log2(K) O(KN) = O(Klog(K)N)
 * space: O(log(K)), stack space
 * Runtime: 28 ms, faster than 58.02% of C++ online submissions
 * Memory Usage: 24.2 MB, less than 5.05% of C++ online submissions
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0)
            return nullptr;
        return binaryMerge(lists, 0, lists.size());
    }
    ListNode* binaryMerge(vector<ListNode*>& lists, int l, int r) {
        if (r - l <= 1)
            return lists[l];
        int m = l + (r - l) / 2;
        ListNode* lN = binaryMerge(lists, l, m);
        ListNode* rN = binaryMerge(lists, m, r);
        ListNode* dummy = new ListNode();
        ListNode* n = dummy;
        while (lN != nullptr && rN != nullptr) {
            if (lN->val < rN->val) {
                ListNode* next = lN->next;
                n->next = lN;
                lN = next;
            } else {
                ListNode* next = rN->next;
                n->next = rN;
                rN = next;
            }
            n = n->next;
        }
        if (lN != nullptr)
            n->next = lN;
        else
            n->next = rN;
        ListNode* ret = dummy->next;
        delete dummy;
        return ret;
    }
};
