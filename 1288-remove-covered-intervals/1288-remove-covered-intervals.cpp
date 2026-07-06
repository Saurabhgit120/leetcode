class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) return a[1] > b[1];  
            return a[0] < b[0];
        });

        int count = 0;
        int prevEnd = 0;  
        bool first = true;
        int maxEnd = INT_MIN;

        for (auto& iv : intervals) {
            if (first || iv[1] > maxEnd) {
                count++;
                maxEnd = iv[1];
                first = false;
            }
             
        }

        return count;
    }
};