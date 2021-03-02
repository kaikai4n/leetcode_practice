/*
 * https://leetcode.com/problems/maximum-subarray/
*/

#include <iostream>
#include <string>
#include <vector>

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
    int maxSubArrayMethod2(vector<int>& nums) {
        /*
         * Divide and conquer
         * time: O(log(n)), space: O(log(n)), implicit stack space
         * Runtime: 40 ms, faster than 6.83% of C++ online submissions
         * Memory Usage: 34.7 MB, less than 6.38% of C++ online submissions
        */
        vector<int> res = divideAndConquer(nums, 0, nums.size());
        return max3(res[0], res[1], res[2]);
    }
    vector<int> divideAndConquer(vector<int>& nums, int l, int r) {
        // return vector<int>{lMax, mMax, rMax, sum}
        if (r - l <= 1)
            return vector<int>{nums[l], nums[l], nums[l], nums[l]};
        int m = l + (r - l) / 2;
        vector<int> lRes = divideAndConquer(nums, l, m);
        vector<int> rRes = divideAndConquer(nums, m, r);
        int lMax = max(lRes[0], lRes[3] + rRes[0]);
        int rMax = max(rRes[2], rRes[3] + lRes[2]);
        int mMax = max3(lRes[1], rRes[1], lRes[2] + rRes[0]);
        int sum = lRes[3] + rRes[3];
        return vector<int>{lMax, mMax, rMax, sum};
    }
    int max3(int a, int b, int c) {
        if (a > b)
            return (a > c) ? a : c;
        else
            return (b > c) ? b : c;
    }
    int max3(vector<int>& nums) {
        return max3(nums[0], nums[1], nums[2]);
    }
    int maxSubArrayMethod1(vector<int>& nums) {
        /*
         * Method: Record the minimum prefix sum. Deduct the current
         *      prefix sum with the minimum prefix sum and compare
         *      with the maximum recorded value. Return the maximum
         *      recorded value.
         * time: O(n), space: O(1)
         * Runtime: 8 ms, faster than 73.28% of C++ online submissions
         * Memory Usage: 13.2 MB, less than 70.70% of C++ online submissions
        */
        int minAcc = 0, maxVal = nums[0], acc = 0;
        for (int i = 0; i < nums.size(); i ++) {
            acc += nums[i];
            maxVal = max(maxVal, acc - minAcc);
            minAcc = min(minAcc, acc);
        }
        return maxVal;
    }
};


int main() {
    string input;
    cin >> input >> input >> input;
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
    cout << "solution = " << sol.maxSubArrayMethod2(inputVec) << endl;
}
