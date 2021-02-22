/*
 * https://leetcode.com/problems/student-attendance-record-i/
 * Runtime: 0 ms, faster than 100.00% of C++ online submissions
 * Memory Usage: 6.2 MB, less than 53.47% of C++ online submissions
*/

#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    bool checkRecord(string s) {
        int cntA = 0, accL = 0;
        for (char c: s) {
            if (c == 'A')
                cntA ++;
            if (c == 'L')
                accL ++;
            else
                accL = 0;
            if (cntA > 1 || accL > 2)
                return false;
        }
        return true;
    }
};


int main() {
    string input;
    cin >> input;
    input = input.substr(1, input.length() - 2);
    cout << "input = \"" << input << "\"" << endl;
    Solution sol;
    cout << "solution = " << sol.checkRecord(input) << endl;
}
