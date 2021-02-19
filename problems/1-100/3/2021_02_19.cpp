/*
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * method: Use pointers to records start and end index of substrings
 *      with no repeating chars. A vector of size 256 is created to 
 *      know if the next pointed char is repeated.
 * time: O(S), space: O(1)
 * Runtime: 0 ms, faster than 100.00% of C++ online submissions
 * Memory Usage: 6.8 MB, less than 95.83% of C++ online submissions
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() == 0)
            return 0;
        vector<bool> traveled(256, false);
        int l = 0, r = 1;
        traveled[s[0]] = true;
        int maxCnt = 1;
        while (r < s.length()) {
            if (traveled[s[r]]) {
                while (s[l] != s[r])
                    traveled[s[l ++]] = false;
                l ++;
            } else {
                maxCnt = max(maxCnt, r - l + 1);
                traveled[s[r]] = true;
            }
            r ++;
        }
        return maxCnt;
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    cout << "input = \"" << input << "\"" << endl;
    Solution sol;
    cout << "solution = " << sol.lengthOfLongestSubstring(input) << endl;
}
