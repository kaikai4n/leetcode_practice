#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    const int modNum = 1000000007;
    int checkRecordMethod1(int n) {
        /* dynamic programming with 6 state trasitions:
         *  state 0: no A, last is not L
         *  state 1: no A, last is L, but last 2 is not L
         *  state 2: no A, last 2 are LL
         *  state 3, 4, and 5 are one A and L status similar
         *      to state 0, 1, and 2.
         *  DP relation:
         *      s0' = s0 + s1 + s2
         *      s1' = s0
         *      s2' = s1
         *      s3' = s0 + s1 + s2 + s3 + s4 + s5
         *      s4' = s3
         *      s5' = s4
         *  time: O(n), space: O(1)
         * Runtime: 144 ms, faster than 52.98% of C++ online submissions
         * Memory Usage: 5.8 MB, less than 98.01% of C++ online submissions
        */
        if (n <= 0)
            return 0;
        vector<int> dp0{1, 1, 0, 1, 0, 0};
        vector<int> dp1(6, 0);
        for (int i = 2; i <= n; i ++) {
            vector<int>& dpNow = (i % 2 == 0) ? dp0 : dp1;
            vector<int>& dpNext = (i % 2 == 0) ? dp1 : dp0;
            dpNext[0] = sum3(dpNow[0], dpNow[1], dpNow[2]);
            dpNext[1] = dpNow[0];
            dpNext[2] = dpNow[1];
            dpNext[3] = sum6(dpNow);
            dpNext[4] = dpNow[3];
            dpNext[5] = dpNow[4];
        }
        vector<int>& dpNow = (n % 2 == 1) ? dp0 : dp1;
        int res = sum6(dpNow);
        return res;
    }
    int sum2(int a, int b) {
        return (a + b) % modNum;
    }
    int sum3(int a, int b, int c) {
        return sum2(sum2(a, b), c);
    }
    int sum6(vector<int>& vec) {
        return sum2(sum3(vec[0], vec[1], vec[2]), sum3(vec[3], vec[4], vec[5]));
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    int n = stoi(input);
    Solution sol;
    cout << "solution = " << sol.checkRecord(n) << endl;
}
