/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii
 * time: O(n), space: O(n)
 * Runtime: 128 ms, faster than 87.12% of C++ online submissions
 * Memory Usage: 79.8 MB, less than 40.64% of C++ online submissions
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
        vector<pair<int, int>> lMaxVal{make_pair(-1, 0)};
        for (int lMin = nonDecPairs[0].first, i = 0; i < nonDecPairs.size() - 1; i ++) {
            if (nonDecPairs[i].first < lMin)
                lMin = nonDecPairs[i].first;
            if (nonDecPairs[i].second - lMin > lMaxVal.back().second)
                lMaxVal.push_back(make_pair(i, nonDecPairs[i].second - lMin));
        }
        // right-to-left
        vector<pair<int, int>> rMaxVal{make_pair(nonDecPairs.size(), 0)};
        for (int rMax = nonDecPairs.back().second, i = nonDecPairs.size() - 1; i > 0; i --) {
            if (nonDecPairs[i].second > rMax)
                rMax = nonDecPairs[i].second;
            if (rMax - nonDecPairs[i].first > rMaxVal.back().second)
                rMaxVal.push_back(make_pair(i, rMax - nonDecPairs[i].first));
        }
        // Find the max profit by summing the two solutions
        int maxProfit = 0;
        for (int l = 1, r = rMaxVal.size() - 1; l < lMaxVal.size(); l ++) {
            while (lMaxVal[l].first >= rMaxVal[r].first) {
                r --;
                if (r == 0)
                    break;
            }
            if (lMaxVal[l].second + rMaxVal[r].second > maxProfit)
                maxProfit = lMaxVal[l].second + rMaxVal[r].second;
        }
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
