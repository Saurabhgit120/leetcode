class Solution {
public:
    int minJumps(vector<vector<int>>& jump, int start, int end, int level) {
        if (start == end)
            return 0;

        if (jump[start][0] >= end)
            return 1;

        if (jump[start][level] < end)
            return INT_MAX;

        int j;
        for (j = level; j >= 0; --j) {
            if (jump[start][j] < end)
                break;
        }

        return (1 << j) + minJumps(jump, jump[start][j], end, j);
    }

    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {
        vector<pair<int,int>> a;
        for (int i = 0; i < n; i++)
            a.push_back({nums[i], i});

        sort(a.begin(), a.end());

        vector<int> sortedNums(n), pos(n);
        for (int i = 0; i < n; i++) {
            sortedNums[i] = a[i].first;
            pos[a[i].second] = i;
        }

        int LOG = 32 - __builtin_clz(n) + 1;

        vector<vector<int>> jump(n, vector<int>(LOG));

        int r = 0;
        for (int i = 0; i < n; i++) {
            while (r + 1 < n && sortedNums[r + 1] - sortedNums[i] <= maxDiff)
                r++;
            jump[i][0] = r;
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                jump[i][k] = jump[jump[i][k - 1]][k - 1];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int u = pos[q[0]];
            int v = pos[q[1]];

            if (u > v)
                swap(u, v);

            int res = minJumps(jump, u, v, LOG - 1);

            if (res == INT_MAX)
                ans.push_back(-1);
            else
                ans.push_back(res);
        }

        return ans;
    }
};