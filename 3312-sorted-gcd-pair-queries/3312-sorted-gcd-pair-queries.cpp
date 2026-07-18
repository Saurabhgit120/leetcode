class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        
        vector<int> cnt(mx + 1, 0);
        for (int x : nums) cnt[x]++;

        
        vector<long long> cntG(mx + 1, 0);

        
        for (int g = mx; g >= 1; g--) {
            long long divisible = 0;

            for (int multiple = g; multiple <= mx; multiple += g) {
                divisible += cnt[multiple];
                cntG[g] -= cntG[multiple];
            }

            cntG[g] += divisible * (divisible - 1) / 2;
        }

        
        for (int i = 2; i <= mx; i++)
            cntG[i] += cntG[i - 1];

        vector<int> ans;

        for (long long q : queries) {
            ans.push_back(
                upper_bound(cntG.begin(), cntG.end(), q) - cntG.begin()
            );
        }

        return ans;
    }
};