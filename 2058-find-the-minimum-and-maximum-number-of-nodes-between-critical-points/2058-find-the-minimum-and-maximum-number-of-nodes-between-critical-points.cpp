class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        if (!head || !head->next || !head->next->next)
            return ans;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;
        int first = -1;
        int last = -1;
        int minDist = INT_MAX;

        while (curr->next) {
            // Critical point: local maximum or local minimum
            if ((curr->val > prev->val && curr->val > curr->next->val) ||
                (curr->val < prev->val && curr->val < curr->next->val)) {

                if (first == -1) {
                    first = index;
                } else {
                    minDist = min(minDist, index - last);
                }

                last = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        // Need at least two critical points
        if (first == last)
            return ans;

        int maxDist = last - first;

        ans[0] = minDist;
        ans[1] = maxDist;

        return ans;
    }
};