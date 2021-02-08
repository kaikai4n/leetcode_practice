/*
 * https://leetcode.com/problems/distinct-subsequences
 * method: 
 *  1. construct indexes of s categorized by the 52 alphabets in sAlphaIdx
 *  2. for each char in t:
 *      sum the total occurrences before the index in previous sAlphaIdx
 *  3. sum the last occurrences as output
 * example: s = "babgbag", t = "bag"
 *  1. sAlphaIdx['a'] = [1, 5], ['b'] = [0, 2, 4], ['g'] = [3, 6]
 *  2-a. when t = 'b', prev = {0: 1, 2: 1, 4: 1}
 *  2-b. when t = 'a', prev = {1: 1, 5: 3}
 *  2-c. when t = 'g', prev = {3: 1, 6: 4}
 *  3. sum(value of prev) = 1 + 4 = 5
 * time: O(ST), space: O(S)
 * Runtime: 0 ms, faster than 100.00% of C++ online submissions
 * Memory Usage: 6.6 MB, less than 91.63% of C++ online submissions
*/


#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;


class Solution {
public:
    int numDistinct(string s, string t) {
        if (t.length() == 0)
            return s.length() + 1;
        vector<vector<int>> sAlphaRec(this->totalAlpha);
        // time: O(S), space: O(S)
        for(int sI = 0; sI < s.length(); sI ++)
            sAlphaRec[this->alphaToIdx(s[sI])].push_back(sI);
        // space of prev is less than O(S)
        vector<int> prev0(sAlphaRec[this->alphaToIdx(t[0])].size(), 1);
        vector<int> prev1;
        for (int tI = 1; tI < t.length(); tI ++) {
            bool isZero = (tI % 2 == 1);
            vector<int>& prev = (isZero) ? prev0 : prev1;
            vector<int>& next = (isZero) ? prev1 : prev0;
            // for each target char
            // calculate the sum based on previous sum and save in next
            // time: O(TS), space: O(S)
            int sumNow = 0, prevI = 0;
            vector<int> prevSAlphaRec = sAlphaRec[this->alphaToIdx(t[tI - 1])];
            for (int sI: sAlphaRec[this->alphaToIdx(t[tI])]) {
                if (prevI == prev.size())
                    next.push_back(sumNow);
                else if (sI < prevSAlphaRec[0])
                    next.push_back(0);
                else {
                    while (prevI < prev.size() && prevSAlphaRec[prevI] < sI) {
                        if (INT_MAX - prev[prevI] < sumNow)  // prevent overflow, since the answer is guaranteed not to overflow
                            break;
                        sumNow += prev[prevI];
                        prevI ++;
                    }
                    next.push_back(sumNow);
                }
            }
            prev.clear();
        }
        int res = 0;
        for (int num: ((t.length() % 2 == 1) ? prev0 : prev1))
            res += num;
        return res;
    }
private:
    const int totalAlpha = 52;
    int alphaToIdx(char c) {
        int residual = c - 'A';
        if (residual > 25)
            return c - 'a' + 26;
        return residual;
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 3);
    string s(input);
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    string t(input);
    cout << "s = \"" << s << "\", t = \"" << t << "\"" << endl;
    Solution sol;
    cout << "solution = " << sol.numDistinct(s, t) << endl;
}
