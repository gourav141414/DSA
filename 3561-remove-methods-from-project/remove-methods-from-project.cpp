class Solution {
public:
    void dfs(int u, vector<vector<int>>& adj, vector<bool>& suspicious) {
        suspicious[u] = true;

        for (int v : adj[u]) {
            if (!suspicious[v])
                dfs(v, adj, suspicious);
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        vector<bool> suspicious(n, false);

        // Build graph
        for (auto &e : invocations)
            adj[e[0]].push_back(e[1]);

        // Step 1: Find all suspicious methods
        dfs(k, adj, suspicious);

        // Step 2: Check if any outside method calls a suspicious method
        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            if (!suspicious[u] && suspicious[v]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        // Step 3: Return remaining methods
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};