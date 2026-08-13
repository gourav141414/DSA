class Solution {
    struct Node {
        int pre, suf, best, len;
        char lc, rc;
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {
        Node res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.pre = a.pre;
        res.suf = b.suf;
        res.best = max(a.best, b.best);

        if (a.rc == b.lc) {
            if (a.pre == a.len)
                res.pre = a.len + b.pre;

            if (b.suf == b.len)
                res.suf = b.len + a.suf;

            res.best = max(res.best, a.suf + b.pre);
        }

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = {1, 1, 1, 1, s[l], s[l]};
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, char c) {
        if (l == r) {
            s[pos] = c;
            tree[node] = {1, 1, 1, 1, c, c};
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, c);
        else
            update(node * 2 + 1, mid + 1, r, pos, c);

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

public:
    vector<int> longestRepeating(string s,
                                 string queryCharacters,
                                 vector<int>& queryIndices) {
        this->s = s;

        int n = s.size();
        tree.resize(4 * n);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            update(1, 0, n - 1,
                   queryIndices[i],
                   queryCharacters[i]);

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};