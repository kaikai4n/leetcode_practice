/*
 * https://leetcode.com/problems/zigzag-conversion/
 * method: calculate the moded idx and append to last of output
 * time: O(S), space: O(1)
 * Runtime: 8 ms, faster than 89.14% of C++ online submissions
 * Memory Usage: 8.2 MB, less than 80.44% of C++ online submissions
*/
#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1)
            return s;
        string res;
        int modNum = 2 * numRows - 2;
        for (int i = 0; i < s.length(); i += modNum)
            res += s[i];
        for (int l = 1, r = modNum - 1; l < numRows - 1; l ++, r --) {
            int t = 0;
            for (; r + t * modNum < s.length(); t ++) {
                res += s[l + t * modNum];
                res += s[r + t * modNum];
            }
            if (l + t * modNum < s.length())
                res += s[l + t * modNum];
        }
        for (int i = numRows - 1; i < s.length(); i += modNum)
            res += s[i];
        return res;
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    string s(input.substr(1, input.length() - 3));
    cin >> input >> input >> input;
    int numRows = stoi(input);
    cout << "s = \"" << s << "\", numRows = " << numRows << endl;
    Solution sol;
    cout << "solution = \"" << sol.convert(s, numRows) << "\"" << endl;
}
