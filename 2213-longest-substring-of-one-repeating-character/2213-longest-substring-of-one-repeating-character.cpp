class Solution {
public:
    struct Node {
        int len;
        int leftChar, rightChar;
        int pref, suff, best;

        Node() : len(0), leftChar(-1), rightChar(-1),
                 pref(0), suff(0), best(0) {}
    };

    vector<Node> seg;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        res.pref = a.pref;
        if (a.pref == a.len && a.rightChar == b.leftChar)
            res.pref += b.pref;

        res.suff = b.suff;
        if (b.suff == b.len && a.rightChar == b.leftChar)
            res.suff += a.suff;

        res.best = max(a.best, b.best);
        if (a.rightChar == b.leftChar)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int p, int l, int r) {
        if (l == r) {
            seg[p].len = 1;
            seg[p].leftChar = seg[p].rightChar = s[l];
            seg[p].pref = seg[p].suff = seg[p].best = 1;
            return;
        }

        int m = (l + r) / 2;
        build(p * 2, l, m);
        build(p * 2 + 1, m + 1, r);

        seg[p] = merge(seg[p * 2], seg[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, char c) {
        if (l == r) {
            seg[p].leftChar = seg[p].rightChar = c;
            seg[p].pref = seg[p].suff = seg[p].best = 1;
            return;
        }

        int m = (l + r) / 2;

        if (idx <= m)
            update(p * 2, l, m, idx, c);
        else
            update(p * 2 + 1, m + 1, r, idx, c);

        seg[p] = merge(seg[p * 2], seg[p * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        this->s = s;

        int n = s.size();
        seg.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            int idx = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, idx, c);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};