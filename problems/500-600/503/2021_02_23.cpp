/*
 * https://leetcode.com/problems/next-greater-element-ii/
 * time: O(n), space: O(n)
 * Runtime: 28 ms, faster than 95.34% of C++ online submissions
 * Memory Usage: 23.8 MB, less than 78.08% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;


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


class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        if (nums.size() == 0)
            return nums;
        stack<int> s;
        vector<int> res(nums.size(), -1);
        int maxNum = nums[0];
        for (int i = 0; i < nums.size(); i ++) {
            maxNum = max(maxNum, nums[i]);
            while (!s.empty() && nums[i] > nums[s.top()]) {
                res[s.top()] = nums[i];
                s.pop();
            }
            s.push(i);
        }
        int i = 0;
        while (!s.empty()) {
            while (!s.empty() && nums[i] > nums[s.top()]) {
                res[s.top()] = nums[i];
                s.pop();
            }
            if (maxNum == nums[s.top()])  // repeat to the largest value
                break;
            i ++;
        }
        return res;
    }
};


int main() {
    string input;
    cin >> input;
    input = input.substr(1, input.length() - 2);
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
    Solution sol;
    printVector("solution", sol.nextGreaterElements(inputVec));
}
