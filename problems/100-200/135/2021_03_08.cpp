/*
 * https://leetcode.com/problems/candy/
 * method1: Two pass forward and backward.
 *          time: O(n), space: O(n)
 * method2: One forward pass and backward when decreasing.
 *          time: O(n), space: O(1)
*/

class Solution {
public:
    int candyMethod2(vector<int>& ratings) {
        /*
         * Runtime: 16 ms, faster than 97.11% of C++ online submissions
         * Memory Usage: 17.2 MB, less than 97.73% of C++ online submissions
        */
        int res = 0, sum = 1;
        int i = 0;
        while (i < ratings.size()) {
            if (i + 1 < ratings.size()) {
                if (ratings[i + 1] > ratings[i]) {
                    res += sum;
                    sum ++;
                    i ++;
                } else if (ratings[i + 1] == ratings[i]) {
                    res += sum;
                    sum = 1;
                    i ++;
                } else {
                    int j = i;
                    while (j + 1 < ratings.size() && ratings[j] > ratings[j + 1])
                        j ++;
                    int revSum = 2, nextI = j;
                    j --;
                    while (j != i) {
                        res += revSum;
                        revSum ++;
                        j --;
                    }
                    res += max(sum, revSum);
                    sum = 1;
                    i = nextI;
                }
            } else {
                res += sum;
                i ++;
            }
        }
        return res;
    }
    int candyMethod1(vector<int>& ratings) {
        /*
         * Runtime: 16 ms, faster than 97.11% of C++ online submissions
         * Memory Usage: 17.7 MB, less than 67.17% of C++ online submissions
        */
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
