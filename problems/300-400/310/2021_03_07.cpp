/*
 * https://leetcode.com/problems/minimum-height-trees/
 * Method:
 *      1. Start dfs search for one node, and record the node
 *         with the maximum diameter from the start node.
 *      2. Start dfs search from the previous node and record
 *         the maximum diameter of the tree.
 *      3. Dfs again from the previous node and get the middle
 *         nodes on the diameter paths.
 *      Note that the middle middle nodes are the ones to find.
 *      If there are longer path start from the middle nodes,
 *      then we can prove by contradiction that there are longer
 *      diameter of the tree.
 * time: O(n), space: O(V + E), where V is # of vertices and E is 
 *      # of edges.
 * Runtime: 56 ms, faster than 98.99% of C++ online submissions 
 * Memory Usage: 28.6 MB, less than 73.58% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjEdges(n);
        for (const vector<int>& edge: edges) {
            adjEdges[edge[0]].push_back(edge[1]);
            adjEdges[edge[1]].push_back(edge[0]);
        }
        auto sn = dfsGetStartNode(0, n, adjEdges);
        auto sn2 = dfsGetStartNode(0, n, adjEdges);
        int maxHeight = sn2.first, maxNode = sn2.second;
        vector<int> res;
        vector<bool> traveled(n, false);
        vector<bool> traveledRes(n, false);
        vector<int> pathNodes;
        dfsGetMiddleFromMaxNode(maxNode, traveled, n, adjEdges, 1, maxHeight, res, pathNodes, traveledRes);
        return res;
    }
    pair<int, int> dfsGetStartNode(int startNode, int n, vector<vector<int>>& adjEdges) {
        vector<bool> traveled(n, false);
        int maxHeight = 1, maxNode = 0;
        dfsStartNode(0, traveled, n, adjEdges, 1, maxHeight, maxNode);
        return {maxHeight, maxNode};
    }
    void dfsStartNode(int node, vector<bool>& traveled, int n, vector<vector<int>>& adjEdges, int heightNow, int& maxHeight, int& maxNode) {
        if (heightNow > maxHeight) {
            maxHeight = heightNow;
            maxNode = node;
        }
        traveled[node] = true;
        for (int newNode: adjEdges[node])
            if (!traveled[newNode])
                dfsStartNode(newNode, traveled, n, adjEdges, heightNow + 1, maxHeight, maxNode);
    }
    void dfsGetMiddleFromMaxNode(int node, vector<bool>& traveled, int n, vector<vector<int>>& adjEdges, int heightNow, int& maxHeight, vector<int>& res, vector<int>& pathNodes, vector<bool>& traveledRes) {
        // cout << "node = " << node << endl;
        pathNodes.push_back(node);
        traveled[node] = true;
        for (int newNode: adjEdges[node])
            if (!traveled[newNode]) 
                dfsGetMiddleFromMaxNode(newNode, traveled, n, adjEdges, heightNow + 1, maxHeight, res, pathNodes, traveledRes);
        if (heightNow >= maxHeight) {
            if (heightNow > maxHeight) {
                maxHeight = heightNow;
                res.clear();
                for (int i = 0; i < n; i ++)
                    traveledRes[i] = false;
            }
            // cout << "heightNow = maxHeight = " << maxHeight << endl;
            recordInRes(res, pathNodes, pathNodes.size() / 2, traveledRes);
            if (pathNodes.size() % 2 == 0)
                recordInRes(res, pathNodes, pathNodes.size() / 2 - 1, traveledRes);
        }
        pathNodes.pop_back();
    }
    void recordInRes(vector<int>& res, vector<int>& pathNodes, int i, vector<bool>& traveledRes) {
        int node = pathNodes[i];
        if (!traveledRes[node]) {
            res.push_back(node);
            traveledRes[node] = true;
        }
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


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(0, input.length() - 1);
    int n = stoi(input);
    cout << "n = " << n << endl;
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
    printVector("solution", sol.findMinHeightTrees(n, inputVec));
}
