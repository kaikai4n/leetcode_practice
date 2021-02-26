/*
 * https://leetcode.com/problems/median-of-two-sorted-arrays/
 * Method: Binary search the smaller nums vector.
 * time: O(log(min(m, n))), space: O(log(min(m, n)))
 * Runtime: 36 ms, faster than 65.75% of C++ online submissions
 * Memory Usage: 89 MB, less than 84.97% of C++ online submissions
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
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            // swap to assure any cut in nums1 can find the median cut
            // in nums2
            return binarySearch(nums2, nums1, 0, nums2.size());
        } else
            return binarySearch(nums1, nums2, 0, nums1.size());
    }
    double binarySearch(vector<int>& nums1, vector<int>& nums2, int l, int r) {
        // cout << "l = " << l << ", r = " << r << endl;
        if (l >= r) {
            int l2 = nums2CutIdx(nums1, nums2, l);
            // cout << "m = " << l << ", m2 = " << l2 << endl;
            return getMedian(nums1, nums2, l, l2);
        }
        int m = l + (r - l) / 2;
        int m2 = nums2CutIdx(nums1, nums2, m);
        // cout << "m = " << m << ", m2 = " << m2 << endl;
        bool nums1G2 = (m2 == 0 || nums1[m] >= nums2[m2 - 1]);
        bool nums2G1 = (m == 0 || nums2[m2] >= nums1[m - 1]);
        if (nums1G2 && nums2G1) {
            // found the median cut
            return getMedian(nums1, nums2, m, m2);
        } else if (nums1G2)
            return binarySearch(nums1, nums2, l, m - 1);
        else
            return binarySearch(nums1, nums2, m + 1, r);
    }
    int nums2CutIdx(vector<int>& nums1, vector<int>& nums2, int l1) {
        return (nums1.size() + nums2.size()) / 2 - l1;
    }
    double getMedian(vector<int>& nums1, vector<int>& nums2, int m, int m2) {
        if ((nums1.size() + nums2.size()) % 2 == 1) {
            if (m >= nums1.size())
                return double(nums2[m2]);
            else if (m2 >= nums2.size())
                return double(nums1[m]);
            else
                return min(nums1[m], nums2[m2]);
        } else {
            int smaller;
            if (m == 0)
                smaller = nums2[m2 - 1];
            else if (m2 == 0)
                smaller = nums1[m - 1];
            else
                smaller = max(nums1[m - 1], nums2[m2 - 1]);
            int larger;
            if (m >= nums1.size())
                larger = nums2[m2];
            else if (m2 >= nums2.size())
                larger = nums1[m];
            else
                larger = min(nums1[m], nums2[m2]);
            return (double(larger) + double(smaller)) / 2;
        }
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
    printVector("nums1", inputVec);
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
    printVector("nums2", inputVec2);
    Solution sol;
    cout << "solution = " << sol.findMedianSortedArrays(inputVec, inputVec2) << endl;
}
