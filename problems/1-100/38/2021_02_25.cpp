/*
 * https://leetcode.com/problems/count-and-say/
 * Runtime: 4 ms, faster than 92.48% of C++ online submissions
 * Memory Usage: 6.6 MB, less than 66.24% of C++ online submissions
*/

class Solution {
public:
    string countAndSay(int n) {
        if (n == 1)
            return string{"1"};
        string s = countAndSay(n - 1);
        string res;
        int i = 0;
        while (i < s.length()) {
            int cnt = 1;
            while (i + 1 < s.length() && s[i] == s[i + 1]) {
                i ++;
                cnt ++;
            }
            res += to_string(cnt);
            res += s[i];
            i ++;
        }
        return res;
    }
};
