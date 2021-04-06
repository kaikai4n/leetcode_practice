/*
 * https://leetcode.com/problems/word-break/
 * Method: Use dynamic programming table "dp[i]" to record
 *      Whether s[1:i] can "wordBreak" by wordDict.
 * time: O(|s| * |w|), space: O(|s|), where |s| is the length
 *      of the string "s" and |w| is the total characters in
 *      the wordDict.
 * Runtime: 0 ms, faster than 100.00% of C++ online submissions
 * Memory Usage: 7.6 MB, less than 91.99% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.length(); i ++) {
            if (dp[i - 1]) {
                for (string& word: wordDict) {
                    if (!dp[i - 1 + word.length()] && s.substr(i - 1, word.length()) == word)
                        dp[i - 1 + word.length()] = true;
                }
            }
        }
        return dp[s.length()];
    }
};


void printVector(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "\"" << input << "\"";
    }
    cout << "]" << endl;
}


int main() {
    string input;
    cin >> input >> input >> input;
    string s(input.substr(1, input.length() - 3));
    cout << "s = \"" << s << "\"" << endl;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    vector<string> inputVec;
    string delim(",");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec.push_back(input.substr(1, idx - 2));
        input = input.substr(idx + delim.length());
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec.push_back(input.substr(1, input.length() - 2));
    printVector("input", inputVec);
    Solution sol;
    cout << sol.wordBreak(s, inputVec) << endl;
}
