/*
 * https://leetcode.com/problems/palindrome-partitioning-ii/
 * method:
 *      1. Construct isPalim[i][j] to check if s[i:j] is a palimdrome
 *          with dynamic programming. Same strategy as problem 131.
 *          The construction time and space are O(S^2).
 *      2. Construct minCuts[j] to get the minimum cuts for substring
 *          s[0:j]. The time is O(S^2) and space is O(S).
 * time: O(S^2), space: O(S)
 * Runtime: 24 ms, faster than 75.51% of C++ online submissions
 * Memory Usage: 7.3 MB, less than 71.85% of C++ online submissions
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    int minCut(string s) {
        int sLen = s.length();
        // Record whether s[i:j] is a palindrome in isPalim 2D vector
        vector<vector<bool>> isPalim(sLen, vector<bool>(sLen, false));
        for(int r = 0; r < sLen; r ++) {
            for (int l = r; l >= 0; l --) {
                if (l == r)
                    isPalim[l][r] = true;
                else if (l == r - 1)
                    isPalim[l][r] = s[l] == s[r];
                else if (s[l] == s[r] && isPalim[l + 1][r - 1])
                    isPalim[l][r] = true;
            }
        }
        // Record the minimum cuts for s[0:j] in minCuts vector
        vector<int> minCuts(sLen, 0);
        for (int r = 1; r < sLen; r ++) {
            if (isPalim[0][r]) {
                minCuts[r] = 0;
            } else {
                minCuts[r] = r;
                for (int l = r; l > 0; l --)
                    if (isPalim[l][r] && minCuts[l - 1] + 1 < minCuts[r])
                        minCuts[r] = minCuts[l - 1] + 1;
            }
        }
        return minCuts[sLen - 1];
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    cout << "input = \"" << input << "\"" << endl;
    Solution sol;
    cout << "solution = " << sol.minCut(input) << endl;
}
