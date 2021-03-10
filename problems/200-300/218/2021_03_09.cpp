/*
 * https://leetcode.com/problems/the-skyline-problem/
 * Method: Divide and conquer
 * time: O(nlog(n)), space: O(n)
 * Runtime: 72 ms, faster than 32.76% of C++ online submissions
 * Memory Usage: 54.8 MB, less than 7.99% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;


class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        if (buildings.size() == 0)
            return vector<vector<int>>{};
        return dac(buildings, 0, buildings.size());
    }
    vector<vector<int>> dac(vector<vector<int>>& buildings, int l, int r) {
        if (r - l <= 1)
            return vector<vector<int>>{{buildings[l][0], buildings[l][2]}, {buildings[l][1], 0}};
        int m = l + (r - l) / 2;
        vector<vector<int>> lB = dac(buildings, l, m);
        vector<vector<int>> rB = dac(buildings, m, r);
        int lI = 0, rI = 0, prevHeight = 0;
        vector<vector<int>> res;
        while (lI < lB.size() && rI < rB.size()) {
            int thisIdx, thisHeight;
            if (lB[lI][0] < rB[rI][0]) {
                // merge lB
                thisIdx = lB[lI][0];
                thisHeight = max(lB[lI][1], (rI - 1 >= 0) ? rB[rI - 1][1] : 0);
                lI ++;
            } else if (lB[lI][0] > rB[rI][0]) {
                // merge rB
                thisIdx = rB[rI][0];
                thisHeight = max(rB[rI][1], (lI - 1 >= 0) ? lB[lI - 1][1] : 0);
                rI ++;
            } else {
                // equal starting index, eliminate the lower-height one
                thisIdx = lB[lI][0];
                thisHeight = max(lB[lI][1], rB[rI][1]);
                lI ++;
                rI ++;
            }
            if (thisHeight != prevHeight) {
                res.push_back(vector<int>{thisIdx, thisHeight});
                prevHeight = thisHeight;
            }
        }
        while (lI < lB.size())
            res.push_back(lB[lI ++]);
        while (rI < rB.size())
            res.push_back(rB[rI ++]);
        return res;
    }
};


vector<int> getSubInput(string input) {
    input = input.substr(1, input.length() - 2);
    string delim(",");
    vector<int> out;
    auto idx = input.find(delim);
    while (idx != string::npos) {
        out.push_back(stoi(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        out.push_back(stoi(input));
    return out;
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


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    vector<vector<int>> inputVec;
    string delim(",[");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec.push_back(getSubInput(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec.push_back(getSubInput(input));
    printVectorOfVector("input", inputVec);
    Solution sol;
    printVectorOfVector("solution", sol.getSkyline(inputVec));
}
