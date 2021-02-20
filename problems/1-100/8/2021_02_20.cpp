/*
 * https://leetcode.com/problems/string-to-integer-atoi/
 * Runtime: 4 ms, faster than 66.05% of C++ online submissions
 * Memory Usage: 7 MB, less than 58.19% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <limits.h>

using namespace std;


class Solution {
public:
    int myAtoi(string s) {
        int res = 0;
        int i = 0;
        // step 1: read space
        while (i < s.length() && s[i] == ' ')
            i ++;
        // step 2: check sign
        bool isNeg = false;
        if (i < s.length() && s[i] == '-') {
            isNeg = true;
            i ++;
        } else if (i < s.length() && s[i] == '+')
            i ++;
        // step 3: read till the end of digits
        while (i < s.length() && 0 <= s[i] - '0' && s[i] - '0' <= 9 && res != INT_MIN && res != INT_MAX) {
            if (isNeg) {
                if (res < (INT_MIN + (s[i] - '0')) / 10)
                    res = INT_MIN;
                else
                    res = 10 * res - (s[i] - '0');
            } else {
                if (res > (INT_MAX - (s[i] - '0')) / 10)
                    res = INT_MAX;
                else
                    res = 10 * res + (s[i] - '0');
            }
            i ++;
        }
        return res;
    }
};


int main() {
    string input;
    getline(cin, input, '"');
    getline(cin, input, '"');
    cout << "input = \"" << input << "\"" << endl;
    Solution sol;
    cout << "solution = " << sol.myAtoi(input) << endl;
}
