/*
 * https://leetcode.com/problems/longest-valid-parentheses/
 * Method: Use a stack to record the previous balance.
 * time: O(S), space: O(S)
 * Runtime: 8 ms, faster than 32.53% of C++ online submissions
 * Memory Usage: 7.5 MB, less than 43.50% of C++ online submissions
*/

class Solution {
public:
    int longestValidParentheses(string s) {
        int balance = 0;
        int longest = 0;
        if (s.length() == 0)
            return 0;
        stack<pair<int, int>> st;
        for (int i = 0; i < s.length(); i ++) {
            char c = s[i];
            if (c == '(') {
                if (st.empty() || balance > st.top().second)
                    st.push({i, balance});
                balance ++;
            } else {
                balance --;
                while (!st.empty() && balance != st.top().second)
                    st.pop();
                if (!st.empty())
                    longest = max(longest, i - st.top().first + 1);
            }
        }
        return longest;
    }
};
