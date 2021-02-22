/*
 * https://leetcode.com/problems/gas-station/
 * time: O(n), space: O(1)
 * Runtime: 4 ms, faster than 93.55% of C++ online submissions
 * Memory Usage: 9.8 MB, less than 67.87% of C++ online submissions
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
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int acc = gas[0] - cost[0];
        int sIdx = 0, sAcc = acc;
        for (int i = 1; i < gas.size(); i ++) {
            acc += gas[i] - cost[i];
            if (acc < sAcc) {
                sAcc = acc;
                sIdx = i;
            }
        }
        if (acc < 0)
            return -1;
        return (sIdx + 1) % gas.size();
    }
};


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
    printVector("gas", inputVec);
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    vector<int> inputVec2;
    idx = input.find(delim);
    while (idx != string::npos) {
        inputVec2.push_back(stoi(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec2.push_back(stoi(input));
    printVector("cost", inputVec2);
    Solution sol;
    cout << "solution = " << sol.canCompleteCircuit(inputVec, inputVec2) << endl;
}
