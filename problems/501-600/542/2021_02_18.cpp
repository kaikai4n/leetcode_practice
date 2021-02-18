/*
 * https://leetcode.com/problems/01-matrix/
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <limits.h>

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
    const vector<int> dH{0, 1, 0, -1};
    const vector<int> dW{1, 0, -1, 0};
    vector<vector<int>> updateMatrixMethod1(vector<vector<int>>& matrix) {
        /*
         * method: bfs with pruning
         * time: O(rc), space: O(rc)
         * Runtime: 104 ms, faster than 58.97% of C++ online submissions
         * Memory Usage: 36.1 MB, less than 20.33% of C++ online submissions
        */
        int H = matrix.size();
        if (H == 0)
            return matrix;
        int W = matrix[0].size();
        queue<pair<int, int>> q;
        for (int h = 0; h < H; h ++)
            for (int w = 0; w < W; w ++)
                if (matrix[h][w] == 0)
                    for (int dI = 0; dI < dH.size(); dI ++)
                        q.push(make_pair(h + dH[dI], w + dW[dI]));
        int dist = -1;
        while (!q.empty()) {
            int qSize = q.size();
            for (int qI = 0; qI < qSize; qI ++) {
                auto qFrontEle = q.front(); q.pop();
                int h = qFrontEle.first, w = qFrontEle.second;
                if (h < 0 || w < 0 || h >= H || w >= W || matrix[h][w] == 0)
                    continue;
                if (matrix[h][w] == 1) {
                    matrix[h][w] = dist;
                    for (int dI = 0; dI < dH.size(); dI ++)
                        q.push(make_pair(h + dH[dI], w + dW[dI]));
                }
            }
            dist --;
        }
        for (int h = 0; h < H; h ++)
            for (int w = 0; w < W; w ++)
                matrix[h][w] = -matrix[h][w];
        return matrix;
    }
    vector<vector<int>> updateMatrixMethod2(vector<vector<int>>& matrix) {
        /*
         * method: use dynamic programming to travel from top-left to
         *      bottom-right and vise versa. The reason is that there
         *      are four directions to perform bfs, if we halve the
         *      directions to right and down, and left and up, then
         *      this is what exactly the two travels of dynamic
         *      programming try to solve.
         * time: O(rc), space: O(rc)
         * Runtime: 56 ms, faster than 97.92% of C++ online submissions
         * Memory Usage: 26.2 MB, less than 88.88% of C++ online submissions
        */
        int H = matrix.size();
        if (H == 0)
            return matrix;
        int W = matrix[0].size();
        vector<vector<int>> ret(H, vector<int>(W));
        ret[0][0] = (matrix[0][0] == 0) ? 0 : INT_MAX;
        for (int w = 1; w < W; w ++)
            if (matrix[0][w] == 0)
                ret[0][w] = 0;
            else
                ret[0][w] = (ret[0][w - 1] == INT_MAX) ? INT_MAX : ret[0][w - 1] + 1;
        for (int h = 1; h < H; h ++)
            if (matrix[h][0] == 0)
                ret[h][0] = 0;
            else
                ret[h][0] = (ret[h - 1][0] == INT_MAX) ? INT_MAX : ret[h - 1][0] + 1;
        for (int h = 1; h < H; h ++)
            for (int w = 1; w < W; w ++)
                if (matrix[h][w] == 0)
                    ret[h][w] = 0;
                else
                    ret[h][w] = min((ret[h - 1][w] == INT_MAX) ? INT_MAX - 1 : ret[h - 1][w],
                                    (ret[h][w - 1] == INT_MAX) ? INT_MAX - 1 : ret[h][w - 1])
                                + 1;
        for (int w = W - 2; w >= 0; w --)
            if (matrix[H - 1][w] != 0)
                ret[H - 1][w] = min(ret[H - 1][w], (ret[H - 1][w + 1] == INT_MAX) ? INT_MAX : ret[H - 1][w + 1] + 1);
        for (int h = H - 2; h >= 0; h --)
            if (matrix[h][W - 1] != 0)
                ret[h][W - 1] = min(ret[h][W - 1], (ret[h + 1][W - 1] == INT_MAX) ? INT_MAX : ret[h + 1][W - 1] + 1);
        for (int h = H - 2; h >= 0; h --)
            for (int w = W - 2; w >= 0; w --)
                if (matrix[h][w] != 0)
                    ret[h][w] = min(ret[h][w],
                                    min((ret[h + 1][w] == INT_MAX) ? INT_MAX - 1 : ret[h + 1][w],
                                        (ret[h][w + 1] == INT_MAX) ? INT_MAX - 1 : ret[h][w + 1])
                                    + 1);
        return ret;
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
    printVectorOfVector("solution", sol.updateMatrixMethod2(inputVec));
}
