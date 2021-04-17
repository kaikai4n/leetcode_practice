class Solution {
public:
    int lengthOfLISBinarySearch(vector<int>& nums) {
        /*
         * DP + BinarySearch: time: O(nlog(n)), space: O(n)
         * Runtime: 8 ms, faster than 89.93% of C++ online submissions
         * Memory Usage: 10.3 MB, less than 81.21% of C++ online submissions
        */
        vector<int> res;
        for (int num: nums) {
            if (res.size() == 0 || num > res.back())
                res.push_back(num);
            else
                res[binarySearchIdx(res, num)] = num;
        }
        return res.size();
    }
    int binarySearchIdx(vector<int> &nums, int num) {
        int l = 0, r = nums.size() - 1;
        while (r > l) {
            int m = l + (r - l) / 2;
            if (nums[m] == num)
                return m;
            else if (nums[m] > num)
                r = m - 1;
            else
                l = m + 1;
        }
        return (nums[l] < num) ? l + 1 : l;
    }
    int lengthOfLISDP(vector<int>& nums) {
        /*
         * DP method: time: O(n^2), space: O(n)
         * Runtime: 272 ms, faster than 30.59% of C++ online submissions
         * Memory Usage: 10.5 MB, less than 59.13% of C++ online submissions
        */
        int n = nums.size();
        vector<int> dp(n, 1);
        int res = 1;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < i; j ++) {
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], 1 + dp[j]);
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
