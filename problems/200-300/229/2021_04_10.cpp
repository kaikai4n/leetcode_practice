/*
 * https://leetcode.com/problems/majority-element-ii/
 * Boyer-Moore Voting Algorithm
 * time: O(n), space: O(1)
 * Runtime: 12 ms, faster than 69.28% of C++ online submissions
 * Memory Usage: 15.7 MB, less than 77.52% of C++ online submissions
*/

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int candidate1, cnt1 = 0, candidate2, cnt2 = 0;
        for (int num: nums) {
            if (cnt1 == 0 && !(cnt2 != 0 && candidate2 == num)) {
                candidate1 = num;
                cnt1 = 1;
                continue;
            } else if (cnt2 == 0 && candidate1 != num) {
                candidate2 = num;
                cnt2 = 1;
                continue;
            }
            if (cnt1 != 0)
                cnt1 += (candidate1 == num) ? 1 : (candidate2 == num) ? 0 : -1;
            if (cnt2 != 0)
                cnt2 += (candidate2 == num) ? 1 : (candidate1 == num) ? 0 : -1;
        }
        // check the candidates to have ratio greater than 1/3
        vector<int> res;
        if (cnt1 > 0){
            cnt1 = 0;
            for (int num: nums)
                if (num == candidate1)
                    cnt1 ++;
            if (cnt1 > nums.size() / 3)
                res.push_back(candidate1);
        }
        if (cnt2 > 0){
            cnt2 = 0;
            for (int num: nums)
                if (num == candidate2)
                    cnt2 ++;
            if (cnt2 > nums.size() / 3)
                res.push_back(candidate2);
        }
        return res;
    }
};
