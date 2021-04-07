/*
 * https://leetcode.com/problems/find-the-duplicate-number/
 * Runtime: 8 ms, faster than 73.36% of C++ online submissions
 * Memory Usage: 11 MB, less than 35.01% of C++ online submissions
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size() - 1; i ++) {
            while (nums[i] != i + 1) {
                if (nums[i] - 1 < i || nums[i] == nums[nums[i] - 1])
                    return nums[i];
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        return nums[nums.size() - 1];
    }
};
