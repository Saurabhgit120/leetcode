class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> pos;

        // Store positions of all 1s
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1')
                pos.push_back(i);
        }

        if (pos.size() < k)
            return "";

        string ans = "";

        for (int i = 0; i + k - 1 < pos.size(); i++) {
            int l = pos[i];
            int r = pos[i + k - 1];

            string cur = s.substr(l, r - l + 1);

            if (ans.empty() ||
                cur.size() < ans.size() ||
                (cur.size() == ans.size() && cur < ans)) {
                ans = cur;
            }
        }

        return ans;
    }
};