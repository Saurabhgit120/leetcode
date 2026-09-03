class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;
        int minEven = INT_MAX;

        for (int x : nums1) {
            if (x & 1)
                minOdd = min(minOdd, x);
            else
                minEven = min(minEven, x);
        }

        // All numbers are even.
        if (minOdd == INT_MAX)
            return true;

        // If there are even numbers, the smallest odd
        // must be smaller than every even number.
        if (minEven != INT_MAX && minOdd > minEven)
            return false;

        return true;
    }
};