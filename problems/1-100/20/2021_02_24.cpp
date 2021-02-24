/*
 * https://leetcode.com/problems/valid-parentheses/
 * time: O(n), space: O(n)
 * Runtime: 0 ms, faster than 100.00% of C++ online submissions
 * Memory Usage: 6.3 MB, less than 73.23% of C++ online submissions
*/

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c: s) {
            if (c == '(' || c == '[' || c == '{')
                st.push(c);
            else {
                if (st.empty())
                    return false;
                if ((c == ')' && st.top() == '(') || 
                    (c == ']' && st.top() == '[') || 
                    (c == '}' && st.top() == '{'))
                    st.pop();
                else
                    return false;
            }
        }
        return st.empty();
    }
};
