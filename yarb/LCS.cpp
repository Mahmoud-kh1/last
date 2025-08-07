#include <bits/stdc++.h>
using namespace std;

// dp[idx][sz] = minimum index in s (0..n) at which you can finish
// matching a subsequence of length sz drawn from t[0..idx].
// If impossible, it will be >= n.
static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        string s, t;
        cin >> s >> t;
        int n = s.size();
        int m = t.size();

        // 1) Build next-occurrence table:
        //    nxt[i][c] = smallest j >= i with s[j] = 'a'+c, or n if none.
        vector<array<int,26>> nxt(n+1);
        // Initialize row n to all “no occurrence” = n
        for (int c = 0; c < 26; ++c) 
            nxt[n][c] = n;
        // Fill backward
        for (int i = n - 1; i >= 0; --i) {
            nxt[i] = nxt[i+1];
            nxt[i][ s[i] - 'a' ] = i;
        }

        // 2) Prepare memo tables
        // dp has dimensions m x (m+1)
        vector<vector<int>> dp(m, vector<int>(m+1, INF));
        vector<vector<bool>> seen(m, vector<bool>(m+1, false));

        // 3) Recursive lambda for dp
        function<int(int,int)> solve = [&](int idx, int sz) -> int {
            if (sz == 0) 
                return -1;       // match empty subsequence before s starts
            if (idx < 0) 
                return n;        // need >0 chars but no t left ⇒ impossible
            if (seen[idx][sz]) 
                return dp[idx][sz];
            seen[idx][sz] = true;

            // Option 1: skip t[idx]
            int best = solve(idx-1, sz);

            // Option 2: take t[idx] as the last char of our sz-length subsequence
            int prevPos = solve(idx-1, sz-1);
            if (prevPos < n) {
                // jump to next occurrence of t[idx] after prevPos
                int c = t[idx] - 'a';
                int nextPos = nxt[prevPos+1][c];
                best = min(best, nextPos);
            }

            return dp[idx][sz] = best;
        };

        // 4) Find largest sz (0..m) such that dp(m-1,sz) < n
        int answer = 0;
        for (int sz = m; sz >= 0; --sz) {
            if (solve(m-1, sz) < n) {
                answer = sz;
                break;
            }
        }

        cout << answer << "\n";
    }

    return 0;
}
