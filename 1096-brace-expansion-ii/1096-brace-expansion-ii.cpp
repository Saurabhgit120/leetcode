class Solution {
public:
    set<string> parse(string &s, int &i) {
        set<string> res;
        set<string> cur = {""};

        while (i < s.size() && s[i] != '}') {
            if (s[i] == ',') {
                res.insert(cur.begin(), cur.end());
                cur = {""};
                i++;
            }
            else if (s[i] == '{') {
                i++;
                set<string> temp = parse(s, i);
                i++; // Skip '}'

                set<string> newCur;
                for (auto &a : cur) {
                    for (auto &b : temp) {
                        newCur.insert(a + b);
                    }
                }
                cur = newCur;
            }
            else {
                string ch(1, s[i]);
                set<string> newCur;

                for (auto &a : cur) {
                    newCur.insert(a + ch);
                }
                cur = newCur;
                i++;
            }
        }

        res.insert(cur.begin(), cur.end());
        return res;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> res = parse(expression, i);
        return vector<string>(res.begin(), res.end());
    }
};