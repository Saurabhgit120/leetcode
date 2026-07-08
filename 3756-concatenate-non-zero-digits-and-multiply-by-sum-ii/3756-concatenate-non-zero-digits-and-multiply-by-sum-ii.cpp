 
class Solution {
public:
    static const int MOD = 1e9 + 7;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> digits, pos;
        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                digits.push_back(s[i] - '0');
                pos.push_back(i);
            }
        }

        int m = digits.size();

        vector<long long> pow10(m + 1, 1), prefNum(m + 1, 0), prefSum(m + 1, 0);
        for (int i = 0; i < m; i++) {
            pow10[i + 1] = (pow10[i] * 10) % MOD;
            prefNum[i + 1] = (prefNum[i] * 10 + digits[i]) % MOD;
            prefSum[i + 1] = prefSum[i] + digits[i];
        }

        vector<int> first(n, -1), last(n, -1);

        int p = 0;
        for (int i = 0; i < n; i++) {
            while (p < m && pos[p] < i) p++;
            first[i] = (p < m ? p : -1);
        }

        p = m - 1;
        for (int i = n - 1; i >= 0; i--) {
            while (p >= 0 && pos[p] > i) p--;
            last[i] = p;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = first[q[0]];
            int r = last[q[1]];

            if (l == -1 || r == -1 || l > r) {
                ans.push_back(0);
                continue;
            }

            long long num =
                (prefNum[r + 1] - prefNum[l] * pow10[r - l + 1] % MOD + MOD) % MOD;

            long long sum = prefSum[r + 1] - prefSum[l];

            ans.push_back((num * sum) % MOD);
        }

        return ans;
    }
};