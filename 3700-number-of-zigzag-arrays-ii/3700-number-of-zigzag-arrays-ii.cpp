class Solution {
public:
    int zigZagArrays(long long n, int l, int r) {
    const long long MOD = 1e9 + 7;
    int m = r - l + 1;
    int sz = 2 * m;

    using Matrix = vector<vector<long long>>;

    auto multiply = [&](const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < n; j++) {
                    if (B[k][j] == 0) continue;
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        return C;
    };

    auto matpow = [&](Matrix base, long long exp) {
        int n = base.size();
        Matrix result(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) result[i][i] = 1;
        while (exp > 0) {
            if (exp & 1) result = multiply(result, base);
            base = multiply(base, base);
            exp >>= 1;
        }
        return result;
    };

    Matrix T(sz, vector<long long>(sz, 0));
    for (int x = 0; x < m; x++) {
        for (int y = x + 1; y < m; y++) T[y][x + m] = 1;   // up[x] -> down[y]
        for (int y = 0; y < x; y++)     T[y + m][x] = 1;   // down[x] -> up[y]
    }

    vector<long long> start(sz, 1);
    Matrix P = matpow(T, n - 1);

    long long ans = 0;
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            ans = (ans + P[i][j] * start[j]) % MOD;

    return (int)ans;
}
};