/*
 * https://leetcode.com/problems/longest-valid-parentheses/
 * MethodStack and MethodStackOpt: time and space: O(S)
*/

class Solution {
public:
    int longestValidParenthesesMethodStackOpt(string s) {
        /*
         * Method: An optimized stack solution
         * time: O(S), space: O(S)
         * Runtime: 4 ms, faster than 85.45% of C++ online submissions
         * Memory Usage: 7.2 MB, less than 62.10% of C++ online submissions
        */
        int longest = 0;
        if (s.length() == 0)
            return 0;
        stack<int> st;
        st.push(-1);
        for (int i = 0; i < s.length(); i ++) {
            char c = s[i];
            if (c == '(') {
                st.push(i);
            } else {
                st.pop();
                if (!st.empty())
                    longest = max(longest, i - st.top());
                else
                    st.push(i);
            }
        }
        return longest;
    }
    int longestValidParenthesesMethodStack(string s) {
        /*
         * Method: Use a stack to record the previous balance.
         * time: O(S), space: O(S)
         * Runtime: 8 ms, faster than 32.53% of C++ online submissions
         * Memory Usage: 7.5 MB, less than 43.50% of C++ online submissions
         */
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
