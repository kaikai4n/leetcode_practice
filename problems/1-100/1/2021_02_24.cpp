class Solution {
public:
    vector<int> twoSumOnePass(vector<int>& nums, int target) {
        /*
        Method: merging the two pass solution to one pass.
        time: O(n), space: O(n)
        Runtime: 0 ms, faster than 100.00% of C++ online submissions
        Memory Usage: 8.9 MB, less than 71.94% of C++ online submissions
        */
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i ++) {
            int k = target - nums[i];
            if (m.find(k) != m.end())
                return vector<int>{m[k], i};
            m[nums[i]] = i;
        }
        return vector<int>{};
    }
    vector<int> twoSumTwoPass(vector<int>& nums, int target) {
        /*
        Method: the first pass records the num in a hash table, the
            second pass finds the solution whether in the hash table.
        time: O(n), space: O(n)
        Runtime: 8 ms, faster than 74.84% of C++ online submissions
        Memory Usage: 11.3 MB, less than 6.14% of C++ online submissions
        */
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < nums.size(); i ++)
            m[nums[i]].push_back(i);
        for (int i = 0; i < nums.size(); i ++) {
            int k = target - nums[i];
            if (k != nums[i] && m[k].size() > 0)
                return vector<int>{i, m[k][0]};
            else if (k == nums[i] && m[k].size() > 1)
                return m[k];
        }
        return vector<int>{};
    }
};
