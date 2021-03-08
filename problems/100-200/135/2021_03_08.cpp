/*
 * https://leetcode.com/problems/candy/
 * time: O(n), space: O(n)
 * Runtime: 16 ms, faster than 97.11% of C++ online submissions
 * Memory Usage: 17.7 MB, less than 67.17% of C++ online submissions
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if (ratings.size() == 0)
            return 0;
        else if (ratings.size() == 1)
            return 1;
        vector<int> res(ratings.size(), 1);
        for (int i = 1, sum = 1; i < ratings.size(); i ++) {
            if (ratings[i] > ratings[i - 1])
                sum ++;
            else
                sum = 1;
            res[i] = sum;
        }
        for (int i = ratings.size() - 2, sum = res[ratings.size() - 1]; i >= 0; i --) {
            if (ratings[i] > ratings[i + 1])
                sum ++;
            else
                sum = 1;
            res[i] = max(res[i], sum);
        }
        int out = 0;
        for (const int& oneRes: res)
            out += oneRes;
        return out;
    }
};
