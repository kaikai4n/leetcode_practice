/*
 * https://leetcode.com/problems/super-washing-machines/
 * Linear: time: O(n), space: O(1)
 * NSquare: time: O(n^2), space: O(n)
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    int findMinMovesLinear(vector<int>& machines) {
        /*
         * Method: Calculate the max of prefix sum and the distributed postive machine.
         * time: O(n), space: O(1)
         * Runtime: 4 ms, faster than 97.66% of C++ online submissions for Super Washing Machines.
         * Memory Usage: 13 MB, less than 35.09% of C++ online submissions
        */
        int n = machines.size();
        int sum = 0;
        for (int i = 0; i < n; i ++)
            sum += machines[i];
        int avg = sum / n;
        if (avg * n != sum)
            return -1;
        int res = 0;
        for(int prefix = 0, i = 0; i < n; i ++) {
            int machine = machines[i] - avg;
            prefix += machine;
            if (machine > 0)
                res = max(res, machine);
            res = max(res, abs(prefix));
        }
        return res;
    }
    int findMinMovesNSquare(vector<int>& machines) {
        /*
         * Method: Fix the first element, then find the next opposite sign 
         *         to make up the difference.
         * time: O(n^2), space: O(n)
        */
        int n = machines.size();
        int sum = 0;
        for (int i = 0; i < n; i ++)
            sum += machines[i];
        int avg = sum / n;
        if (avg * n != sum)
            return -1;
        int res = 0;
        vector<int> lockNum(n, 0);
        for (int i = 0; i < n; i ++) {
            int diff = machines[i] - avg, j = i + 1;
            while (diff != 0) {
                if (diff < 0 && machines[j] - avg > 0) {
                    lockNum[j] += -diff;
                    int makeup = min(-diff, machines[j] - avg);
                    diff += makeup;
                    machines[j] -= makeup;
                } else if (diff > 0 && machines[j] - avg < 0) {
                    int makeup = min(diff, avg - machines[j]);
                    diff -= makeup;
                    machines[j] += makeup;
                } else {
                    lockNum[j] += sign(diff);
                }
                j ++;
            }
            res = max(res, (lockNum[i] + sign(machines[i] - avg)));
        }
        return res;
    }
    int sign(int num) {
        if (num < 0)
            return -num;
        return num;
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
    cout << "solution = " << sol.findMinMoves(inputVec) << endl;
}
