/*
 * https://leetcode.com/problems/next-greater-element-i/
 * time: O(|nums1| + |nums2|), space: O(|nums2|)
 * Runtime: 8 ms, faster than 75.98% of C++ online submissions
 * Memory Usage: 8.8 MB, less than 83.06% of C++ online submissions
*/

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        stack<int> s;
        for (int num: nums2) {
            while (!s.empty() && num > s.top()) {
                m[s.top()] = num;
                s.pop();
            }
            s.push(num);
        }
        while (!s.empty()) {
            m[s.top()] = -1;
            s.pop();
        }
        vector<int> res;
        for (int num: nums1)
            res.push_back(m[num]);
        return res;
    }
};
