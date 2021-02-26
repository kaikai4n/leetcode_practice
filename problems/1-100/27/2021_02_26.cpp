/*
 * https://leetcode.com/problems/remove-element/
 * Runtime: 4 ms, faster than 52.40% of C++ online submissions
 * Memory Usage: 8.7 MB, less than 80.69% of C++ online submissions
*/

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0;
        for (int j = 0; j < nums.size(); j ++) {
            if (nums[j] != val) {
                if (i != j)
                    nums[i] = nums[j];
                i ++;
            }
        }
        return i;
    }
};
