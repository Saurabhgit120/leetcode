class Solution {
public:
    string smallestNumber(string num, long long t) {
        auto [need, ok] = getPrimeCount(t);
        if (!ok) return "-1";

        auto factorCnt = getFactorCount(need);
        if (sumValues(factorCnt) > (int)num.size())
            return construct(factorCnt);

        auto prefixCnt = getPrimeCount(num);

        int firstZero = num.find('0');
        if (firstZero == string::npos) {
            firstZero = num.size();
            if (isSubset(need, prefixCnt))
                return num;
        }

        for (int i = (int)num.size() - 1; i >= 0; i--) {
            int d = num[i] - '0';

            prefixCnt = subtract(prefixCnt, FACTOR[d]);

            int remain = (int)num.size() - 1 - i;

            if (i > firstZero) continue;

            for (int nd = d + 1; nd <= 9; nd++) {
                auto req = getFactorCount(
                    subtract(
                        subtract(need, prefixCnt),
                        FACTOR[nd]
                    )
                );

                if (sumValues(req) <= remain) {
                    int ones = remain - sumValues(req);
                    return num.substr(0, i) +
                           char('0' + nd) +
                           string(ones, '1') +
                           construct(req);
                }
            }
        }

        auto req = getFactorCount(need);
        return string(num.size() + 1 - sumValues(req), '1') + construct(req);
    }

private:
    inline static const vector<unordered_map<int,int>> FACTOR = {
        {},                          //0
        {},                          //1
        {{2,1}},                     //2
        {{3,1}},                     //3
        {{2,2}},                     //4
        {{5,1}},                     //5
        {{2,1},{3,1}},               //6
        {{7,1}},                     //7
        {{2,3}},                     //8
        {{3,2}}                      //9
    };

    pair<unordered_map<int,int>, bool> getPrimeCount(long long t) {
        unordered_map<int,int> cnt = {
            {2,0},{3,0},{5,0},{7,0}
        };

        for (int p : {2,3,5,7}) {
            while (t % p == 0) {
                cnt[p]++;
                t /= p;
            }
        }
        return {cnt, t == 1};
    }

    unordered_map<int,int> getPrimeCount(const string& s) {
        unordered_map<int,int> cnt = {
            {2,0},{3,0},{5,0},{7,0}
        };

        for (char c : s) {
            for (auto &[p,f] : FACTOR[c-'0'])
                cnt[p] += f;
        }
        return cnt;
    }

    unordered_map<int,int> getFactorCount(const unordered_map<int,int>& c) {
        unordered_map<int,int> res;

        int c8 = c.at(2) / 3;
        int rem2 = c.at(2) % 3;

        int c9 = c.at(3) / 2;
        int c3 = c.at(3) % 2;

        int c4 = rem2 / 2;
        int c2 = rem2 % 2;

        int c6 = 0;

        if (c2 && c3) {
            c2 = 0;
            c3 = 0;
            c6 = 1;
        }

        if (c3 && c4) {
            c2 = 1;
            c6 = 1;
            c3 = 0;
            c4 = 0;
        }

        res[2] = c2;
        res[3] = c3;
        res[4] = c4;
        res[5] = c.at(5);
        res[6] = c6;
        res[7] = c.at(7);
        res[8] = c8;
        res[9] = c9;

        return res;
    }

    string construct(const unordered_map<int,int>& cnt) {
        string ans;
        for (int d = 2; d <= 9; d++) {
            auto it = cnt.find(d);
            if (it != cnt.end())
                ans += string(it->second, char('0'+d));
        }
        return ans;
    }

    bool isSubset(const unordered_map<int,int>& a,
                  const unordered_map<int,int>& b) {
        for (auto &[k,v] : a)
            if (b.at(k) < v)
                return false;
        return true;
    }

    unordered_map<int,int> subtract(unordered_map<int,int> a,
                                    const unordered_map<int,int>& b) {
        for (auto &[k,v] : b)
            a[k] = max(0, a[k] - v);
        return a;
    }

    int sumValues(const unordered_map<int,int>& mp) {
        int s = 0;
        for (auto &[_,v] : mp) s += v;
        return s;
    }
};