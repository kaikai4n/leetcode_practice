/*
 * https://leetcode.com/problems/sliding-window-maximum/
 * Method PrefixSuffix: time: O(n), space: O(n)
 * Method Deque: time: O(n), space: O(k)
*/

#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;


class Solution {
public:
    vector<int> maxSlidingWindowPrefixSuffix(vector<int>& nums, int k) {
        /*
         * Runtime: 184 ms, faster than 98.60% of C++ online submissions
         * Memory Usage: 138.7 MB, less than 26.89% of C++ online submissions
        */
        int n = nums.size();
        vector<int> maxPrefix(n);
        for (int i = 0; i < n; i ++) {
            if (i % k == 0)
                maxPrefix[i] = nums[i];
            else
                maxPrefix[i] = max(maxPrefix[i - 1], nums[i]);
        }
        vector<int> maxSuffix(n);
        maxSuffix[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i --) {
            if ((i + 1) % k == 0)
                maxSuffix[i] = nums[i];
            else
                maxSuffix[i] = max(maxSuffix[i + 1], nums[i]);
        }
        vector<int> res;
        for (int i = 0; i < n - k + 1; i ++) {
            if (i % k == 0)
                res.push_back(maxSuffix[i]);
            else
                res.push_back(max(maxPrefix[i + k - 1], maxSuffix[i]));
        }
        return res;
    }
    vector<int> maxSlidingWindowDeque(vector<int>& nums, int k) {
        /*
         * Runtime: 244 ms, faster than 52.04% of C++ online submissions
         * Memory Usage: 131.8 MB, less than 48.14% of C++ online submissions
        */
        deque<int> dq;
        vector<int> res;
        for (int i = 0; i < nums.size(); i ++) {
            while (!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();
            dq.push_back(i);
            if (k - 1 <= i) {
                while (dq.front() <= i - k)
                    dq.pop_front();
                res.push_back(nums[dq.front()]);
            }
        }
        return res;
    }
};


void printVector(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << input;
    }
    cout << "]" << endl;
}


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 3);
    vector<int> inputVec;
    string delim(",");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec.push_back(stoi(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec.push_back(stoi(input));
    printVector("input", inputVec);
    cin >> input >> input >> input;
    int k = stoi(input);
    cout << "k = " << k << endl;
    Solution sol;
    printVector("solution", sol.maxSlidingWindow(inputVec, k));
}
