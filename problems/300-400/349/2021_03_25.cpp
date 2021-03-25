/*
 * https://leetcode.com/problems/intersection-of-two-arrays/
 * Method: Form unordered_set of nums1. Loop through nums2 and check
 *      if the looped number in the set. An additional bool in the 
 *      set denotes whether the number repeated.
 * time: O(nums1.size() + nums2.size()), space: O(min(nums1.size(), nums2.size()))
 * Runtime: 4 ms, faster than 92.02% of C++ online submissions
 * Memory Usage: 10.2 MB, less than 76.79% of C++ online submissions
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, bool> s;
        if (nums1.size() > nums2.size()) {
            // swap to reduce memory size
            swap(nums1, nums2);
        }
        for (const int& num: nums1)
            s[num] = false;
        vector<int> res;
        for (const int& num: nums2) {
            unordered_map<int, bool>::iterator it = s.find(num);
            if (it != s.end() && !it->second){
                res.push_back(num);
                it->second = true;
            }
        }
        return res;
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
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 3);
    vector<int> inputVec1;
    string delim(",");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec1.push_back(stoi(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec1.push_back(stoi(input));
    printVector("input", inputVec1);
    vector<int> inputVec2;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    idx = input.find(delim);
    while (idx != string::npos) {
        inputVec2.push_back(stoi(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec2.push_back(stoi(input));
    printVector("input", inputVec2);
    Solution sol;
    printVector("solution", sol.intersection(inputVec1, inputVec2));
}
