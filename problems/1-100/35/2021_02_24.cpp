/*
 * https://leetcode.com/problems/search-insert-position/
 * time: O(log(n)), space: O(log(n)), stack memory
 * Runtime: 4 ms, faster than 90.05% of C++ online submissions
 * Memory Usage: 9.6 MB, less than 92.04% of C++ online submissions
*/

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return binarySearch(nums, target, 0, nums.size());
    }
    int binarySearch(vector<int>& nums, int target, int l, int r) {
        if (r - l <= 1)
            return (nums[l] >= target) ? l : l + 1;
        int m = l + (r - l) / 2;
        if (target >= nums[m])
            return binarySearch(nums, target, m, r);
        else
            return binarySearch(nums, target, l, m);
    }
};
