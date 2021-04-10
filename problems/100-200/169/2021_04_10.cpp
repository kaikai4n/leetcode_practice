/*
 * https://leetcode.com/problems/majority-element/
 * Boyer-Moore Voting Algorithm
 * time: O(n), space: O(1)
 * Runtime: 12 ms, faster than 95.83% of C++ online submissions
 * Memory Usage: 19.7 MB, less than 31.65% of C++ online submissions
*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 0, candidate;
        for (int num: nums) {
            if (cnt == 0)
                candidate = num;
            cnt += (candidate == num) ? 1 : -1;
        }
        return candidate;
    }
};
