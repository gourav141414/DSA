class Solution {
public:
    int n;
    vector<int> suf;
    int dp[101][101];

    int solve(int i, int M) {
        if (i >= n) return 0;

        if (dp[i][M] != -1)
            return dp[i][M];

        int ans = 0;

        for (int x = 1; x <= 2 * M && i + x <= n; x++) {
            int next = solve(i + x, max(M, x));

            // Total remaining - opponent's best
            ans = max(ans, suf[i] - next);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        suf.assign(n + 1, 0);

        for (int i = n - 1; i >= 0; i--)
            suf[i] = piles[i] + suf[i + 1];

        memset(dp, -1, sizeof(dp));

        return solve(0, 1);
    }
};