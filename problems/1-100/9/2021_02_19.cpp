/*
 * https://leetcode.com/problems/palindrome-number/
 * time: O(n), space: O(1), where n is the number length
 * Runtime: 16 ms, faster than 39.45% of C++ online submissions
 * Memory Usage: 5.9 MB, less than 82.80% of C++ online submissions
*/

#include <iostream>
#include <limits.h>

using namespace std;


class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
        else if (x < 10)
            return true;
        int largestDigit = 10;
        while (INT_MAX / 10 > largestDigit && x / (largestDigit * 10) > 0)
            largestDigit *= 10;
        while (largestDigit >= 10) {
            int l = x / largestDigit;
            int r = x % 10;
            if (l != r)
                return false;
            x -= l * largestDigit;
            x /= 10;
            largestDigit /= 100;
        }
        return true;
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    int x = stoi(input);
    Solution sol;
    cout << "solution = " << sol.isPalindrome(x) << endl;
}
