/*
 * https://leetcode.com/problems/triangle
 * method: 1d dynamic programming
 * time: O(n), space: O(sqrt(n))
 * Runtime: 4 ms, faster than 96.39% of C++ online submissions
 * Memory Usage: 8.4 MB, less than 88.01% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


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
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> dp0{triangle[0]};
        vector<int> dp1;
        for (int level = 1, width = 2; level < triangle.size(); level ++, width ++) {
            bool isOdd = (level % 2 == 1);
            vector<int>& dpNow = isOdd ? dp0 : dp1;
            vector<int>& dpNext = isOdd ? dp1 : dp0;
            dpNext.push_back(triangle[level][0] + dpNow[0]);
            for (int col = 1; col < width - 1; col ++)
                dpNext.push_back(triangle[level][col] + min(dpNow[col - 1], dpNow[col]));
            dpNext.push_back(triangle[level][width - 1] + dpNow[width - 2]);
            dpNow.clear();
        }
        vector<int> finalDp = (triangle.size() % 2 == 1) ? dp0 : dp1;
        int res = finalDp[0];
        for (int val: finalDp)
            if (val < res)
                res = val;
        return res;
    }
};


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
    cout << "solution = " << sol.minimumTotal(inputVec) << endl;
}
