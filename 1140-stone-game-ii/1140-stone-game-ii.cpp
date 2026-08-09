class Solution {
public:
    vector<int> suffix;
    int dp[101][101];
    int n;

    int solve(int i, int M) {
        if (i >= n) return 0;

        if (2 * M >= n - i)
            return suffix[i];

        if (dp[i][M] != -1)
            return dp[i][M];

        int ans = 0;

        for (int x = 1; x <= 2 * M; x++) {
            ans = max(ans, suffix[i] - solve(i + x, max(M, x)));
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        suffix.resize(n + 1, 0);
        for (int i = n - 1; i >= 0; i--)
            suffix[i] = suffix[i + 1] + piles[i];

        memset(dp, -1, sizeof(dp));

        return solve(0, 1);
    }
};