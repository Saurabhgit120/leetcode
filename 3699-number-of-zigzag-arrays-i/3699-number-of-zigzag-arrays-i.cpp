class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const int MOD = 1e9 + 7;
        int m = r - l + 1;

        if (n == 1) return m % MOD;

        vector<long long> up(m), down(m), new_up(m), new_down(m);
        vector<long long> suffix(m + 1), prefix(m + 1);

        for (int v = 0; v < m; v++) {
            up[v] = v;
            down[v] = m - 1 - v;
        }

        for (int i = 0; i < n - 2; i++) {
            suffix[m] = 0;
            for (int v = m - 1; v >= 0; v--)
                suffix[v] = (suffix[v + 1] + up[v]) % MOD;

            prefix[0] = 0;
            for (int v = 0; v < m; v++)
                prefix[v + 1] = (prefix[v] + down[v]) % MOD;

            for (int w = 0; w < m; w++) {
                new_down[w] = suffix[w + 1];
                new_up[w] = prefix[w];
            }

            swap(up, new_up);
            swap(down, new_down);
        }

        long long ans = 0;
        for (int v = 0; v < m; v++)
            ans = (ans + up[v] + down[v]) % MOD;

        return (int)ans;
    }
};