class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++) {
            a.push_back({nums[i], i});
        }

        sort(a.begin(), a.end());

        vector<int> ans(n);

        int i = 0;

        while (i < n) {
            int j = i;

            // Values in the same group can be swapped with each other.
            while (j + 1 < n && a[j + 1].first - a[j].first <= limit) {
                j++;
            }

            // Get original indices of this group
            vector<int> indices;
            for (int k = i; k <= j; k++) {
                indices.push_back(a[k].second);
            }

            sort(indices.begin(), indices.end());

            // Assign sorted values to sorted original positions
            for (int k = i; k <= j; k++) {
                ans[indices[k - i]] = a[k].first;
            }

            i = j + 1;
        }

        return ans;
    }
};