#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

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


void printVectorPairInt(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto ele: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "(" << ele.first << "," << ele.second << ")";
    }
    cout << "]" << endl;
}


class Solution {
public:
    vector<vector<int>> fourSumMethod2(vector<int>& nums, int target) {
        /*
         * method:
         *  1. Sort the nums
         *  2. Loop through two index from left to right, the rest of two
         *     index are found by iteration two end to the middle with
         *     O(n) time. It takes O(n) time, since the nums are sorted.
         * time: O(n^3), space: O(1)
         * Runtime: 60 ms, faster than 67.60% of C++ online submissions
         * Memory Usage: 12.9 MB, less than 85.41% of C++ online submissions
        */
        if (nums.size() < 4)
            return vector<vector<int>>{};
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for (int i = 0; i < nums.size() - 3; i ++) {
            for (int j = i + 1; j < nums.size() - 2; j ++) {
                int l = j + 1, r = nums.size() - 1;
                while (l < r) {
                    int sum = nums[i] + nums[j] + nums[l] + nums[r];
                    if (sum == target) {
                        res.push_back(vector<int>{nums[i], nums[j], nums[l], nums[r]});
                        while (l + 1 < nums.size() - 1 && nums[l] == nums[l + 1])
                            l ++;
                        while (r - 1 > j + 1 && nums[r] == nums[r - 1])
                            r --;
                    }
                    if (sum > target)
                        r --;
                    else
                        l ++;
                }
                while (j + 1 < nums.size() - 2 && nums[j] == nums[j + 1])
                    j ++;
            }
            while (i + 1 < nums.size() - 3 && nums[i] == nums[i + 1])
                i ++;
        }
        return res;
    }

    vector<vector<int>> fourSumMethod1(vector<int>& nums, int target) {
        /*
         * method:
         *  1. Sort the numbers O(nlog(n))
         *  2. Add pairs of index to a hash map, which contains no
         *     duplicated pairs. The duplicated index are stored with
         *     the rightmost one.
         *  3. Loop through two index from left and check if the target
         *     sum is in the hash map. If it is in the hash map, store
         *     results if the pairs index are larger than the looped 
         *     ones. O(n^3).
         * time: O(n^3), space: O(n^2)
         * Runtime: 88 ms, faster than 38.98% of C++ online submissions
         * Memory Usage: 32.3 MB, less than 7.72% of C++ online submissions
        */
        if (nums.size() < 4)
            return vector<vector<int>>{};
        sort(nums.begin(), nums.end());
        unordered_map<int, vector<pair<int, int>>> m;
        for (int j = nums.size() - 1; j > 0; j --) {
            for (int i = j - 1; i >= 0; i --) {
                m[nums[i] + nums[j]].push_back({i, j});
                while (i - 1 >= 0 && nums[i] == nums[i - 1])
                    i --;
            }
            while (j - 1 > 0 && nums[j] == nums[j - 1])
                j --;
        }
        vector<vector<int>> res;
        for (int i = 0; i < nums.size() - 3; i ++) {
            for (int j = i + 1; j < nums.size() - 2; j ++) {
                int k = target - nums[i] - nums[j];
                if (m.find(k) != m.end()) {
                    for (auto p: m[k])
                        if (p.first > j)
                            res.push_back(vector<int>{nums[i], nums[j], nums[p.first], nums[p.second]});
                }
                while (j + 1 < nums.size() - 2 && nums[j] == nums[j + 1])
                    j ++;
            }
            while (i + 1 < nums.size() - 3 && nums[i] == nums[i + 1])
                i ++;
        }
        return res;
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
    printVector("input", inputVec);
    cin >> input >> input >> input;
    int target = stoi(input);
    cout << "target = " << target << endl;
    Solution sol;
    printVectorOfVector("solution", sol.fourSumMethod2(inputVec, target));
}
