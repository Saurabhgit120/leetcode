class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIdx = 0, maxIdx = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] < nums[minIdx])
                minIdx = i;

            if (nums[i] > nums[maxIdx])
                maxIdx = i;
        }

        // Make minIdx the leftmost and maxIdx the rightmost
        if (minIdx > maxIdx)
            swap(minIdx, maxIdx);

        // 3 possible ways:
        // 1. Remove both from the left
        int left = maxIdx + 1;

        // 2. Remove both from the right
        int right = n - minIdx;

        // 3. Remove min from left and max from right
        int both = (minIdx + 1) + (n - maxIdx);

        return min({left, right, both});
    }
};