class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();

        // dp[i] = number of distinct subsequences
        // including empty subsequence using first i characters
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;

        // last[c] = 1-based position of previous occurrence
        vector<int> last(26, 0);

        for (int i = 1; i <= n; i++) {
            int c = s[i - 1] - 'a';

            // Every existing subsequence can either take or skip s[i-1]
            dp[i] = (2 * dp[i - 1]) % MOD;

            // Remove duplicates caused by previous occurrence
            if (last[c] != 0) {
                dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
            }

            last[c] = i;
        }

        // Remove empty subsequence
        return (dp[n] - 1 + MOD) % MOD;
    }
};