/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii
 * time: O(n), space: O(n)
 * Runtime: 124 ms, faster than 91.75% of C++ online submissions
 * Memory Usage: 83 MB, less than 21.63% of C++ online submissions
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


void printVectorOfVector(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "[";
        bool inner = false;
        for (auto ele: input) {
            if (inner)
                cout << ",";
            else
                inner = true;
            cout << ele;
        }
        cout << "]";
    }
    cout << "]" << endl;
}


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Find all non decreasing pairs
        vector<pair<int, int>> nonDecPairs;
        int minP = prices[0];
        for(int i = 0; i < prices.size() - 1; i ++) {
            if (prices[i] > prices[i + 1]) {
                if (minP < prices[i])
                    nonDecPairs.push_back(make_pair(minP, prices[i]));
                minP = prices[i + 1];
            }
        }
        if (minP < prices[prices.size() - 1])
            nonDecPairs.push_back(make_pair(minP, prices[prices.size() - 1]));
        // Condition for zero or only one solution
        if (nonDecPairs.size() == 0)
            return 0;
        else if (nonDecPairs.size() == 1)
            return nonDecPairs[0].second - nonDecPairs[0].first;
        // Now find the two combinations to maximize profit
        // First construct left-to-right and right-to-left single 
        // maximum profit .
        // left-to-right
        vector<int> lMaxVal{0};
        for (int lMin = nonDecPairs[0].first, i = 0; i < nonDecPairs.size() - 1; i ++) {
            if (nonDecPairs[i].first < lMin)
                lMin = nonDecPairs[i].first;
            if (nonDecPairs[i].second - lMin > lMaxVal.back())
                lMaxVal.push_back(nonDecPairs[i].second - lMin);
            else
                lMaxVal.push_back(lMaxVal.back());
        }
        // right-to-left
        vector<int> rMaxVal(nonDecPairs.size(), 0);
        for (int rMax = nonDecPairs.back().second, i = nonDecPairs.size() - 1; i > 0; i --) {
            if (nonDecPairs[i].second > rMax)
                rMax = nonDecPairs[i].second;
            if (rMax - nonDecPairs[i].first > rMaxVal.back())
                rMaxVal[i] = rMax - nonDecPairs[i].first;
            else
                rMaxVal[i] = rMaxVal.back();
        }
        // Find the max profit by summing the two solutions
        int maxProfit = 0;
        for (int i = 1; i < lMaxVal.size(); i ++)
            if (lMaxVal[i] + rMaxVal[i] > maxProfit)
                maxProfit = lMaxVal[i] + rMaxVal[i];
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
