class Solution {
public:
    struct State {
        long long score = 0;
        array<int, 4> ids = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
        int cnt = 0;
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        // ids are already sorted
        for (int i = 0; i < 4; i++) {
            if (a.ids[i] != b.ids[i])
                return a.ids[i] < b.ids[i];
        }

        return false;
    }

    State addIndex(const State& s, int idx, int weight) {
        State res = s;
        res.score += weight;

        // Insert idx into sorted ids
        int pos = res.cnt;

        while (pos > 0 && res.ids[pos - 1] > idx) {
            res.ids[pos] = res.ids[pos - 1];
            pos--;
        }

        res.ids[pos] = idx;
        res.cnt++;

        return res;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<int, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by left endpoint
        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[0] != y[0])
                return x[0] < y[0];

            if (x[1] != y[1])
                return x[1] < y[1];

            return x[3] < y[3];
        });

        vector<int> starts(n);

        for (int i = 0; i < n; i++)
            starts[i] = a[i][0];

        // next[i] = first j such that a[j].left > a[i].right
        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {
            nxt[i] = upper_bound(
                starts.begin(),
                starts.end(),
                a[i][1]
            ) - starts.begin();
        }

        // dp[i][k] = best answer from i onward using at most k intervals
        vector<array<State, 5>> dp(n + 1);

        // Base:
        // dp[n][k] = empty answer, score = 0

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 1; k <= 4; k++) {

                // Option 1: skip interval i
                State skip = dp[i + 1][k];

                // Option 2: take interval i
                State take = addIndex(
                    dp[nxt[i]][k - 1],
                    a[i][3],
                    a[i][2]
                );

                dp[i][k] = better(take, skip)
                         ? take
                         : skip;
            }
        }

        vector<int> ans;

        for (int i = 0; i < dp[0][4].cnt; i++)
            ans.push_back(dp[0][4].ids[i]);

        return ans;
    }
};