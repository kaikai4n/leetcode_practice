/*
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/
 * Method: Each addNum operation finds the inserted or merged interval
 *      in 2D interval vector.
 * time: O(n^2), space: O(n)
 * Runtime: 40 ms, faster than 98.21% of C++ online submissions
 * Memory Usage: 30.8 MB, less than 96.43% of C++ online submissions
*/

class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        intervals.clear();
    }
    
    void addNum(int val) {
        int i = 0;
        while (i < intervals.size() && intervals[i][0] <= val)
            i ++;
        if (i == 0) {
            if (intervals.size() > 0 && intervals[0][0] - 1 == val)
                intervals[0][0] = val;
            else
                intervals.insert(intervals.begin(), vector<int>{val, val});
        } else if (i == intervals.size()) {
            if (intervals.size() > 0) {
                if (intervals.back()[1] + 1 == val)
                    intervals.back()[1] = val;
                else if (intervals.back()[1] < val)
                    intervals.push_back(vector<int>{val, val});
            } else
                intervals.push_back(vector<int>{val, val});
        } else {
            if (intervals[i - 1][1] + 1 == val && intervals[i][0] - 1 == val) {
                intervals[i - 1][1] = intervals[i][1];
                intervals.erase(intervals.begin() + i);
            } else if (intervals[i - 1][1] + 1 == val)
                intervals[i - 1][1] = val;
            else if (intervals[i][0] - 1 == val)
                intervals[i][0] = val;
            else if (val > intervals[i - 1][1])
                intervals.insert(intervals.begin() + i, vector<int>{val, val});
        }
    }
    
    vector<vector<int>> getIntervals() {
        return intervals;
    }
private:
    vector<vector<int>> intervals;
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
