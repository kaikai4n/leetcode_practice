/*
 * https://leetcode.com/problems/course-schedule/
 * DFS Search: time: O(V + E), space: O(V + E)
 * Runtime: 24 ms, faster than 43.26% of C++ online submissions
 * Memory Usage: 17.4 MB, less than 7.52% of C++ online submissions
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        for (auto pre: prerequisites) {
            graph[pre[0]].push_back(pre[1]);
        }
        vector<bool> checkBefore(numCourses, false);
        for (int startNode = 0; startNode < numCourses; startNode ++) {
            if (checkBefore[startNode])
                continue;
            vector<bool> traveled(numCourses, false);
            vector<int> traveledNodes;
            stack<pair<int, bool>> s;
            s.push({startNode, false});
            while (!s.empty()) {
                auto topNode = s.top();
                int node = topNode.first, isEnd = topNode.second;
                s.pop();
                if (isEnd) {
                    traveled[node] = false;
                    continue;
                }
                s.push({node, true});
                traveled[node] = true;
                traveledNodes.push_back(node);
                for (int neighbor: graph[node]) {
                    if (checkBefore[neighbor])
                        continue;
                    else if (traveled[neighbor])
                        return false;
                    else
                        s.push({neighbor, false});
                }
            }
            for (int node: traveledNodes)
                checkBefore[node] = true;
        }
        return true;
    }
};
