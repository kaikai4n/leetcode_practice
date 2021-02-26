/*
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 * Runtime: 8 ms, faster than 91.86% of C++ online submissions
 * Memory Usage: 13.7 MB, less than 50.46% of C++ online submissions
*/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i = 0, j = 0;
        while (j < nums.size()) {
            if (i != j)
                nums[i] = nums[j];
            i ++;
            while (j + 1 < nums.size() && nums[j] == nums[j + 1])
                j ++;
            j ++;
        }
        return i;
    }
};
