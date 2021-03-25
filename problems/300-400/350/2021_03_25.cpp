/*
 * https://leetcode.com/problems/intersection-of-two-arrays-ii/
 * time: O(nums1.size() + nums2.size()), space: O(nums1.size())
 * Runtime: 4 ms, faster than 90.88% of C++ online submissions
 * Memory Usage: 10.4 MB, less than 56.05% of C++ online submissions
*/

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> s;
        if (nums1.size() > nums2.size()) {
            // swap to reduce memory size
            swap(nums1, nums2);
        }
        for (const int& num: nums1) {
            auto it = s.find(num);
            if (it == s.end()) {
                s[num] = 1;
            } else {
                s[num] ++;
            }
        }
        vector<int> res;
        for (const int& num: nums2) {
            unordered_map<int, int>::iterator it = s.find(num);
            if (it != s.end() && it->second > 0) {
                res.push_back(num);
                it->second --;
            }
        }
        return res;
    }
};
