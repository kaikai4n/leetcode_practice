/*
 * https://leetcode.com/problems/linked-list-cycle/
 * Method: fast pointer would reach the slow pointer if there is a loop
 * time: O(n), space: O(1)
 * Runtime: 8 ms, faster than 96.06% of C++ online submissions
 * Memory Usage: 8.1 MB, less than 48.83% of C++ online submissions
*/

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *fastNode = head, *slowNode = head;
        while (fastNode != nullptr && fastNode->next != nullptr) {
            fastNode = fastNode->next->next;
            slowNode = slowNode->next;
            if (fastNode == slowNode)
                return true;
        }
        return false;
    }
};
