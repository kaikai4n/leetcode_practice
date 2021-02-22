/*
 * https://leetcode.com/problems/palindrome-partitioning/
 * method:
 *  1. Construct dp table (SxS) to know substring of s from i to j
 *      is a palindrome or not. That is, dp[i][j] is true if and
 *      only if s[i:j] is a palindrome. The construction time is
 *      O(S^2) and the space is O(S^2).
 *  2. Backtracking all the solutions return them. The backtracking
 *      takes O(2^S * S) time, where 2^S for partition and S for
 *      substr process.
 * Runtime: 96 ms, faster than 87.78% of C++ online submissions
 * Memory Usage: 53.5 MB, less than 63.41% of C++ online submissions
*/ 
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void printVectorOfVectorString(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "[";
        bool inner = false;
        for (auto ele: input) {
            if (inner)
                cout << ",";
            else
                inner = true;
            cout << "\"" << ele << "\"";
        }
        cout << "]";
    }
    cout << "]" << endl;
}


class Solution {
public:
    vector<vector<string>> partition(string s) {
        int sLen = s.length();
        // Record whether s[i:j] is a palindrome in dp 2D vector
        vector<vector<bool>> dp(sLen, vector<bool>(sLen, false));
        for(int r = 0; r < sLen; r ++) {
            for (int l = r; l >= 0; l --) {
                if (l == r)
                    dp[l][r] = true;
                else if (l == r - 1)
                    dp[l][r] = s[l] == s[r];
                else if (s[l] == s[r] && dp[l + 1][r - 1])
                    dp[l][r] = true;
            }
        }
        // 
        vector<string> wSet;
        vector<vector<string>> mSet;
        this->backtracking(s, 0, sLen, dp, wSet, mSet);
        return mSet;
    }
private:
    void backtracking(string s, int l, int sLen, vector<vector<bool>>& dp, vector<string>& wSet, vector<vector<string>>& mSet) {
        if (l == sLen) {
            mSet.push_back(wSet);
            return;
        }
        for (int r = l; r < sLen; r ++) {
            if (dp[l][r]) {
                wSet.push_back(s.substr(l, r - l + 1));
                this->backtracking(s, r + 1, sLen, dp, wSet, mSet);
                wSet.pop_back();
            }
        }
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    cout << "input = \"" << input << "\"" << endl;
    Solution sol;
    printVectorOfVectorString("solution", sol.partition(input));
}
