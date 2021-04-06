/*
 * https://leetcode.com/problems/word-break-ii/
 * time: O(|s| * 2^|s|), space: O(|s| * 2^|s|)
 * Runtime: 0 ms, faster than 100.00% of C++ online submissions
 * Memory Usage: 7.3 MB, less than 65.36% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<vector<int>> dp(s.length() + 1);
        for (int i = 0; i < s.length(); i ++) {
            if (i == 0 || dp[i].size() > 0) {
                for (string& word: wordDict)
                    if (s.substr(i, word.length()) == word)
                        dp[i + word.length()].push_back(i);
            }
        }
        // backtracking
        vector<string> res;
        vector<int> btList{(int) s.length()};
        wordBreakBacktracking(dp, s.length(), s, res, btList);
        return res;
    }
    void wordBreakBacktracking(vector<vector<int>> &dp, int i, string s, vector<string> &res, vector<int> &btList) {
        if (i == 0) {
            string out;
            bool first = true;
            for (int i = btList.size() - 1; i > 0; i --) {
                if (first)
                    first = false;
                else
                    out += " ";
                out = out + s.substr(btList[i], btList[i - 1] - btList[i]);
            }
            res.push_back(out);
            return;
        }
        for (int nextI: dp[i]) {
            btList.push_back(nextI);
            wordBreakBacktracking(dp, nextI, s, res, btList);
            btList.pop_back();
        }
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
    printVector("solution", sol.wordBreak(s, inputVec));
}
