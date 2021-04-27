/*
 * https://leetcode.com/problems/lru-cache/
 * Method:
 *      1. Use a double link list to maintain the put order
 *      2. Use a vector to point a key to its list node
 * time: O(1), space: O(max key number)
 * Runtime: 80 ms, faster than 87.76% of C++ online submissions
 * Memory Usage: 39.8 MB, less than 91.41% of C++ online submissions
*/

class DoubleListNode {
public:
    int key;
    int val;
    DoubleListNode *next;
    DoubleListNode *prev;
    DoubleListNode(): key(0), val(0), next(nullptr), prev(nullptr) {}
    DoubleListNode(int k, int v) : key(k), val(v), next(nullptr), prev(nullptr) {}
    DoubleListNode(int k, int v, DoubleListNode *n, DoubleListNode *p) : key(k), val(v), next(n), prev(p) {}
};

class LRUCache {
public:
    LRUCache(int capacity) {
        /*
         * 1, 2 -> 1, 1 -> 2, 3 -> 1, 3 -> 1, 4 -> 3, 4 -> 3
        */
        root = nullptr;
        end = nullptr;
        maxCapacity = capacity;
        nowCapacity = 0;
        m.clear();
        m.resize(3001);
    }
    
    int get(int key) {
        DoubleListNode *n = m[key];
        if (n == nullptr)
            return -1;
        else {
            put(key, n->val);
            return n->val;
        }
    }
    
    void put(int key, int value) {
        if (maxCapacity == 0)
            return;
        if (m[key] == nullptr) {
            // insert new value to the front
            m[key] = new DoubleListNode(key, value, root, nullptr);
            if (nowCapacity == 0) {
                // initialization
                root = m[key];
                end = m[key];
            } else {
                root->prev = m[key];
                root = m[key];
            }
            // handle the capacity
            if (nowCapacity == maxCapacity) {
                // remove the last in link list
                m[end->key] = nullptr;
                end = end->prev;
                delete end->next;
                end->next = nullptr;
            } else
                nowCapacity ++;
        } else if (m[key] == root) {
            // set the value and do not change the root setting
            m[key]->val = value;
        } else {
            m[key]->val = value;
            DoubleListNode *prev = m[key]->prev;
            DoubleListNode *next = m[key]->next;
            if (m[key] == end)
                end = prev;
            if (prev != nullptr)
                prev->next = next;
            if (next != nullptr)
                next->prev = prev;
            
            m[key]->next = root;
            m[key]->prev = nullptr;
            if (root != nullptr)
                root->prev = m[key];
            root = m[key];
        }
        // printNode(root, end);
    }
private:
    DoubleListNode *root;
    DoubleListNode *end;
    int maxCapacity;
    int nowCapacity;
    vector<DoubleListNode*> m;
    void printNode(DoubleListNode *root, DoubleListNode *end) {
        cout << "root = ";
        if (root == nullptr) {
            cout << "null" << endl;
        } else {
            while (root != nullptr) {
                cout << root->val << " ";
                root = root->next;
            }
            cout << endl;
        }
        cout << "end = ";
        if (end == nullptr)
            cout << "null" << endl;
        else
            cout << end->val << endl;
    }
};
