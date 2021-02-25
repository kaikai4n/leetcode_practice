/*
 * https://leetcode.com/problems/longest-common-prefix/
 * Runtime: 4 ms, faster than 83.60% of C++ online submissions
 * Memory Usage: 9.2 MB, less than 80.07% of C++ online submissions
*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0)
            return "";
        int i = 0;
        bool reachMaxLen = false;
        while (true) {
            char thisChar = 0;
            bool sameChar = true;
            for (const string& str: strs) {
                if (i == str.length()) {
                    reachMaxLen = true;
                    break;
                }
                if (thisChar == 0)
                    thisChar = str[i];
                else if (thisChar != str[i]) {
                    sameChar = false;
                    break;
                }
            }
            if (!sameChar || reachMaxLen)
                break;
            i ++;
        }
        return strs[0].substr(0, i);
    }
};
