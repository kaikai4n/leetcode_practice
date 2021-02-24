/*
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 * time: O(n), space: O(1)
 * Runtime: 4 ms, faster than 94.29% of C++ online submissions
 * Memory Usage: 9.6 MB, less than 83.21% of C++ online submissions
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) {
            int sum = numbers[l] + numbers[r];
            if (sum == target)
                return vector<int>{l + 1, r + 1};
            if (sum > target)
                r --;
            else
                l ++;
        }
        return vector<int>{};
    }
};
