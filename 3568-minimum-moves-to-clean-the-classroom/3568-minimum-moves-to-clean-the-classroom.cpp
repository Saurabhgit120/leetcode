class Solution {
public:
    int minMoves(vector<string>& g, int E) {
        int m = g.size();
        int n = g[0].size();

        int sr = 0, sc = 0;
        vector<pair<int, int>> ls;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (g[r][c] == 'S') {
                    sr = r;
                    sc = c;
                } 
                else if (g[r][c] == 'L') {
                    ls.push_back({r, c});
                }
            }
        }

        int k = ls.size();
        if (k == 0) return 0;

        int ALL = (1 << k) - 1;

        // Which litter bit belongs to each cell
        vector<vector<int>> litterBit(m, vector<int>(n, 0));

        for (int i = 0; i < k; i++) {
            litterBit[ls[i].first][ls[i].second] = (1 << i);
        }

        /*
            best[id] = maximum energy with which we have
                       already reached this (r,c,mask).

            If current energy <= best[id], this state is useless.
        */
        int states = m * n * (1 << k);
        vector<int> best(states, -1);

        auto id = [&](int r, int c, int mask) {
            return (mask * m + r) * n + c;
        };

        struct State {
            short r, c;
            short energy;
            int mask;
        };

        queue<State> q;

        best[id(sr, sc, 0)] = E;
        q.push({(short)sr, (short)sc, (short)E, 0});

        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

        int ans = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto cur = q.front();
                q.pop();

                int r = cur.r;
                int c = cur.c;
                int energy = cur.energy;
                int mask = cur.mask;

                // This state has been dominated by a better state.
                if (energy < best[id(r, c, mask)])
                    continue;

                if (mask == ALL)
                    return ans;

                // No energy => cannot make another move.
                if (energy == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    if (g[nr][nc] == 'X')
                        continue;

                    int ne = energy - 1;

                    int nmask = mask | litterBit[nr][nc];

                    // Recharge
                    if (g[nr][nc] == 'R')
                        ne = E;

                    int nid = id(nr, nc, nmask);

                    /*
                        Same position + same collected litter,
                        but we already have >= energy.
                    */
                    if (ne <= best[nid])
                        continue;

                    best[nid] = ne;

                    q.push({
                        (short)nr,
                        (short)nc,
                        (short)ne,
                        nmask
                    });
                }
            }

            ans++;
        }

        return -1;
    }
};