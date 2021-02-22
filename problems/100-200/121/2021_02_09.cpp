/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * time: O(n), space: O(1)
 * Runtime: 120 ms, faster than 31.70% of C++ online submissions
 * Memory Usage: 93.3 MB, less than 40.37% of C++ online submissions
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
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;
        int minVal = prices[0];
        for (int i = 1; i < prices.size(); i ++)
            if (prices[i] < minVal)
                minVal = prices[i];
            else if (prices[i] - minVal > maxProfit)
                maxProfit = prices[i] - minVal;
        return maxProfit;
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
    cout << "solution = " << sol.maxProfit(inputVec) << endl;
}
