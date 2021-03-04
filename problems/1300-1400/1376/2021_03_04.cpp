/*
 * https://leetcode.com/problems/time-needed-to-inform-all-employees/
 * Runtime: 452 ms, faster than 59.76% of C++ online submissions
 * Memory Usage: 275.8 MB, less than 5.06% of C++ online submissions
*/

class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<int> sum(n, -1);
        for (int i = 0; i < n; i ++) {
            if (sum[i] != -1)
                continue;
            int j = manager[i];
            stack<int> s;
            while (j != -1 && sum[j] == -1) {
                s.push(j);
                j = manager[j];
            }
            int sumNow = 0;
            if (j != -1) {
                sumNow = sum[j];
                s.push(j);
            }
            while (!s.empty()) {
                j = s.top();
                s.pop();
                sumNow += informTime[j];
                if (!s.empty())
                    sum[s.top()] = sumNow;
            }
            sum[i] = sumNow;
        }
        int res = 0;
        for (int i = 0; i < n; i ++)
            res = max(res, sum[i]);
        return res;
    }
};
