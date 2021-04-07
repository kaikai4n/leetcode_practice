/*
 * https://leetcode.com/problems/linked-list-cycle-ii/
 * Method: Use slow and fast pointers to detect whether there is a loop.
 *      Suppose for the slow pointer, it traverses a + k nodes, and for the
 *      fast pointer, it traverses a + b + k nodes, where "a" nodes are not
 *      included in the loop nodes, b nodes are the loop nodes, and k nodes
 *      are the number of nodes that further travels from the returned node.
 *      We can formulate the following suppose the pointers meets for n steps:
 *          a + k = n
 *          a + b + k = 2n.
 *      We get b = n, that is, the number of loop nodes is n.
 *      Furthermore, one can observe that a + k = n = b. This tells that the 
 *      number of nodes from the current meet node to the returned node is 
 *      exactly "a" nodes (from k is the number of nodes that further travels
 *      from the returned node and b - k = a).
 *      As a result, if we travel from both the meet node and the initial node 
 *      for "a" rounds, then they will meet on the returned node.
 * time: O(n), space: O(1)
 * Runtime: 8 ms, faster than 83.20% of C++ online submissions
 * Memory Usage: 7.7 MB, less than 29.32% of C++ online submissions
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fastNode = head, *slowNode = head;
        while (fastNode != nullptr && fastNode->next != nullptr) {
            fastNode = fastNode->next->next;
            slowNode = slowNode->next;
            if (fastNode == slowNode) {
                while (head != slowNode) {
                    head = head->next;
                    slowNode = slowNode->next;
                }
                return head;
            }
        }
        return nullptr;
    }
};
