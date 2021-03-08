/*
 * https://leetcode.com/problems/time-needed-to-inform-all-employees/
 * Method:
 *      For each leaf node,
 *          a. Backtrack its manager to the root or to the manager that has traveled
 *             and record the backtracking path
 *          b. Reverse the path to sum the inform time. Note that the started summation
 *             depends on whether backtracked to the root in step a. Record the inform 
 *             time in a vector as the traveled manager.
 * time: O(n), space: O(n)
 * Runtime: 244 ms, faster than 90.24% of C++ online submissions
 * Memory Usage: 227.4 MB, less than 5.06% of C++ online submissions
*/

class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<int> sum(n, -1);
        int res = 0;
        for (int i = 0; i < n; i ++) {
            if (informTime[i] != 0)  // Only consider the leaf nodes
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
            res = max(res, sum[i]);
        }
        return res;
    }
};
