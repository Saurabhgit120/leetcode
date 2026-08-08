class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[i] = number of characters of word2
        // that can be matched from word1[i...]
        vector<int> suf(n + 1, 0);

        int j = m - 1;

        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && word1[i] == word2[j]) {
                suf[i] = suf[i + 1] + 1;
                j--;
            } else {
                suf[i] = suf[i + 1];
            }
        }

        vector<int> ans;
        int p = 0;
        bool changed = false;

        for (int i = 0; i < n && p < m; i++) {

            // Exact match
            if (word1[i] == word2[p]) {
                ans.push_back(i);
                p++;
            }

            // Change word1[i] -> word2[p]
            else if (!changed) {
                // After using change, remaining word2
                // must be matched exactly.
                if (suf[i + 1] >= m - p - 1) {
                    ans.push_back(i);
                    p++;
                    changed = true;
                }
            }
        }

        if (p == m)
            return ans;

        return {};
    }
};