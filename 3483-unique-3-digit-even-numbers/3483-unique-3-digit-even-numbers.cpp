class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int cnt[10] = {};

        for (int d : digits)
            cnt[d]++;

        int ans = 0;

        for (int num = 100; num <= 998; num += 2) {
            int a = num / 100;
            int b = (num / 10) % 10;
            int c = num % 10;

            int need[10] = {};
            need[a]++;
            need[b]++;
            need[c]++;

            bool possible = true;

            for (int d = 0; d < 10; d++) {
                if (need[d] > cnt[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible)
                ans++;
        }

        return ans;
    }
};