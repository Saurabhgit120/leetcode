class Solution {
public:
    int m, n;
    int dp[105][105][205];

    bool solve(vector<vector<char>>& grid, int i, int j, int bal) {
        if (i >= m || j >= n)
            return false;

        if (grid[i][j] == '(')
            bal++;
        else
            bal--;

        if (bal < 0)
            return false;

        int remaining = (m - 1 - i) + (n - 1 - j);

        if (bal > remaining)
            return false;

        if ((bal + remaining) % 2 != 0)
            return false;

        if (i == m - 1 && j == n - 1)
            return bal == 0;

        int &res = dp[i][j][bal];

        if (res != -1)
            return res;

        bool right = solve(grid, i, j + 1, bal);
        bool down = solve(grid, i + 1, j, bal);

        return res = right || down;
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        if ((m + n - 1) % 2 != 0)
            return false;

        memset(dp, -1, sizeof(dp));

        return solve(grid, 0, 0, 0);
    }
};