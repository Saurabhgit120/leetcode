class Solution {
public:
    struct Node {
        int prod;          // product of entire segment % k
        int cnt[5];        // cnt[r] = number of prefixes with product % k == r

        Node() {
            prod = 1;
            memset(cnt, 0, sizeof(cnt));
        }
    };

    int n, K;
    vector<Node> seg;

    Node merge(Node &L, Node &R) {
        Node res;

        // Product of the complete segment
        res.prod = (L.prod * R.prod) % K;

        // Prefixes completely inside the left segment
        for (int r = 0; r < K; r++) {
            res.cnt[r] += L.cnt[r];
        }

        // Prefixes which take all of left + some prefix of right
        for (int r = 0; r < K; r++) {
            int newRem = (L.prod * r) % K;
            res.cnt[newRem] += R.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            int v = nums[l] % K;

            seg[node].prod = v;
            seg[node].cnt[v] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            val %= K;

            seg[node] = Node();
            seg[node].prod = val;
            seg[node].cnt[val] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);

        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[node];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(node * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(node * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        n = nums.size();
        K = k;

        seg.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // We need prefixes of nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};