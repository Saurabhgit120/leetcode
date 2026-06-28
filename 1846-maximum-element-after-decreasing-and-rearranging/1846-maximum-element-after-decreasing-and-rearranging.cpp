class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        arr[0] = 1;                         // first element must be 1
        
        for (int i = 1; i < arr.size(); i++) {
            // can be at most prev+1 (no increasing allowed, only decreasing)
            arr[i] = min(arr[i], arr[i-1] + 1);
        }
        
        return arr.back();
    }
};