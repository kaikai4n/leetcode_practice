/*
 * https://leetcode.com/problems/single-number-ii/
 * time: O(n), space: O(1)
 * Runtime: 8 ms, faster than 79.03% of C++ online submissions
 * Memory Usage: 9.4 MB, less than 98.81% of C++ online submissions
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int c1 = 0, c2 = 0;
        /*
         * The truth is that I can record the number of appearance for each bit and
         * mod the occurrence with 3. In the end, when all the numbers are recorded,
         * the final occurrence happens to be the one that only appear once.
         * Suppose I want to add (c2[i], c1[i]) with n[i], the transition table is
         *  (c2[i], c1[i])   n[i] == 0   n[i] == 1
         *  (0, 0)           (0, 0)      (0, 1)
         *  (0, 1)           (0, 1)      (1, 0)
         *  (1, 0)           (1, 0)      (0, 0)
         * The recorded occurrence transition formulation is
         *  c2[i] = (~c2[i] & c1[i] & n[i]) | (c2[i] & ~c1[i] & ~n[i])
         *  c1[i] = (~c2[i] & ~c1[i] & n[i]) | (~c2[i] & c1[i] & ~n[i])
        */
        for (int n: nums) {
            // printBits("n", n);
            int newC2 = (~c2 & c1 & n) | (c2 & ~c1 & ~n);
            int newC1 = (~c2 & ~c1 & n) | (~c2 & c1 & ~n);
            c2 = newC2;
            c1 = newC1;
            // printBits("c2", c2);
            // printBits("c1", c1);
        }
        return c1;
    }
    void printBits(string s, int n) {
        cout << s << " = ";
        int one = 1 << 4;
        while (one > 0) {
            if (one & n)
                cout << "1";
            else
                cout << "0";
            one >>= 1;
        }
        cout << endl;
    }
};
