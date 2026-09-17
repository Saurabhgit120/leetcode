class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        // best[i] = minimum length of a valid subarray
        // completely inside arr[0...i]
        vector<int> best(n, INF);

        unordered_map<int, int> mp;
        mp[0] = -1;

        int prefix = 0;
        int ans = INF;
        int minLen = INF;

        for (int i = 0; i < n; i++) {
            prefix += arr[i];

            // If prefix - target exists,
            // subarray (mp[prefix-target] + 1 ... i) has sum target
            if (mp.count(prefix - target)) {
                int j = mp[prefix - target];
                int len = i - j;

                // Combine current subarray with the best
                // non-overlapping subarray before j
                if (j >= 0 && best[j] != INF) {
                    ans = min(ans, len + best[j]);
                }

                // Current subarray can become the best one
                minLen = min(minLen, len);
            }

            // Best valid subarray up to index i
            best[i] = minLen;

            mp[prefix] = i;
        }

        return ans == INF ? -1 : ans;
    }
};