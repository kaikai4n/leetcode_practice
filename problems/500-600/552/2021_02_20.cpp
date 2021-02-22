#include <iostream>
#include <string>
#include <vector>

using namespace std;


void printVectorOfVector(string VarName, auto inputs) {
    cout << VarName << " = [";
    int preLen = VarName.length() + 4;
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << "," << endl;
        else
            outer = true;
        for (int i = 0; i < preLen; i ++)
            cout << " ";
        cout << "[";
        bool inner = false;
        for (auto ele: input) {
            if (inner)
                cout << ",";
            else
                inner = true;
            cout << ele;
        }
        cout << "]";
    }
    cout << "]" << endl;
}


class Solution {
public:
    const int modNum = 1000000007;
    int checkRecordMethod2(int n) {
        /*
         * Method 2, an extension of method 1:
         *  Now write down the state transition matrix T
         *  We do not need to compute T^(n - 1).dot(S0) to get
         *  the resultant state Sn. Instead, after computing T^2,
         *  we can compute T^4 if 4 <= n - 1, and T^8 if 8 <= 
         *  n - 1, and so on. Now the computational cost for 
         *  matrix multiplication reduces from O(n) to O(log(n)).
         *  Yet, the method suffers when considering the overflow 
         *  problem, which can be extremely slow to apply mod 
         *  operations.
         * The following implementation is only valid for n <= 30
         * without integer overflow happening. Besides, the 
         * implementation requires additional O(log(n)) space
         * for the recursive stack memory compared to method 1.
        */
        if (n <= 0)
            return 0;
        vector<vector<int>> trans{{1, 1, 1, 0, 0, 0},
                                  {1, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 0, 0},
                                  {1, 1, 1, 1, 1, 1},
                                  {0, 0, 0, 1, 0, 0},
                                  {0, 0, 0, 0, 1, 0}};
        vector<vector<int>> finalTrans{{1, 0, 0, 0, 0, 0},
                                       {0, 1, 0, 0, 0, 0},
                                       {0, 0, 1, 0, 0, 0},
                                       {0, 0, 0, 1, 0, 0},
                                       {0, 0, 0, 0, 1, 0},
                                       {0, 0, 0, 0, 0, 1}};
        // get T^(n - 1)
        int targetN = n - 1;
        recurMultiplyTrans(trans, 1, finalTrans, targetN);
        // get result sum(T^(n - 1) dot (initial state))
        vector<vector<int>> initState{{1}, {1}, {0}, {1}, {0}, {0}};
        vector<vector<int>> finalState = matrixMultiply(finalTrans, initState);
        int res = 0;
        for (int i = 0; i < finalState.size(); i ++)
            res += finalState[i][0];
        return res;
    }
    void recurMultiplyTrans(vector<vector<int>>& trans, int p, vector<vector<int>>& finalTrans, int& n) {
        if (2 * p <= n) {
            vector<vector<int>> transSqr = squareMatrix(trans);
            recurMultiplyTrans(transSqr, 2 * p, finalTrans, n);
        }
        if (p <= n) {
            finalTrans = matrixMultiply(trans, finalTrans);
            n -= p;
        }
    }
    vector<vector<int>> matrixMultiply(vector<vector<int>>& a, vector<vector<int>>& b) {
        // a matrix multiply b
        int R = a.size(), C = b[0].size();
        vector<vector<int>> res(R, vector<int>(C, 0));
        for (int r = 0; r < R; r ++)
            for (int c = 0; c < C; c ++)
                for (int i = 0; i < a[r].size(); i ++)
                    res[r][c] += a[r][i] * b[i][c];
        return res;
    }
    vector<vector<int>> squareMatrix(vector<vector<int>> a) {
        return matrixMultiply(a, a);
    }

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
    cout << "solution = " << sol.checkRecordMethod1(n) << endl;
}
