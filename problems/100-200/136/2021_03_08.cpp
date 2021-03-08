class Solution {
public:
    int singleNumberMethodHash(vector<int>& nums) {
        /*
         * Use a hash map to store whether the number appeared.
         * time: O(n), space: O(n)
         * Runtime: 40 ms, faster than 29.27% of C++ online submissions
         * Memory Usage: 20 MB, less than 20.28% of C++ online submissions
         */
        unordered_map<int, bool> m;
        for (const int& num: nums) {
            if (m.find(num) == m.end())
                m[num] = false;
            else
                m[num] = true;
        }
        for (const int& num: nums)
            if (m[num] == false)
                return num;
        return -1;
    }
    int singleNumberMethodSort(vector<int>& nums) {
        /*
         * Method: sort then traverse to find the not-paired one.
         * time: O(nlog(n)), space: O(log(n)) for sorting algo.
         * Runtime: 24 ms, faster than 71.01% of C++ online submissions
         * Memory Usage: 16.9 MB, less than 70.06% of C++ online submissions
        */
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; i += 2)
            if (nums[i] != nums[i + 1])
                return nums[i];
        return nums[nums.size() - 1];
    }
};
