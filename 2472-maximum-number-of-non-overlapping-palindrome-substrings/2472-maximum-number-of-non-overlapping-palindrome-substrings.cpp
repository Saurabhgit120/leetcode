class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // dp[i] = maximum number of valid palindromes
        // we can take from s[0 ... i-1]
        vector<int> dp(n + 1, 0);

        // palindrome[i][j] = true if s[i...j] is palindrome
        vector<vector<bool>> palindrome(n, vector<bool>(n, false));

        // Build palindrome table
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] &&
                    (j - i <= 2 || palindrome[i + 1][j - 1])) {
                    palindrome[i][j] = true;
                }
            }
        }

        // DP
        for (int i = 1; i <= n; i++) {
            // Don't use a palindrome ending at i-1
            dp[i] = dp[i - 1];

            // Try every possible starting point
            for (int j = 0; j < i; j++) {
                if (i - j >= k && palindrome[j][i - 1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n];
    }
};