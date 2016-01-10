struct Edge {
    int u, v;
    int w;

    Edge() { }
    Edge(int u0, int v0, int w0): u(u0), v(v0), w(w0) { }
};

int zhuliu(int rt)
{
    // 此算法会破坏原图
    // 请确保无自环
    static int pre[MAXN], id[MAXN], vis[MAXN];
    static int in[MAXN];

    int res = 0;
    for (;;) {
        // 计算 in[]
        memset(pre, 0, sizeof(pre));
        std::fill_n(in + 1, N, 1e30);
        for (int i = 1; i <= tote; ++i) {
            if (chkmin(in[E[i].v], E[i].w))
                pre[E[i].v] = E[i].u;
        }
        pre[rt] = -1;
        for (int i = 1; i <= N; ++i) {
            if (pre[i] == 0)
                return -1;
        }
        in[rt] = 0;
        for (int i = 1; i <= N; ++i) {
            res += in[i];
        }

        // 找环
        int totc = 0;
        memset(id, 0, sizeof(id));
        memset(vis, 0, sizeof(vis));
        vis[rt] = -1;
        for (int i = 1; i <= N; ++i) {
            int u;
            for (u = i; vis[u] == 0; u = pre[u]) {
                vis[u] = i;
            }
            if (vis[u] == i) {
                id[u] = ++totc;
                for (int v = pre[u]; v != u; v = pre[v]) {
                    id[v] = totc;
                }
            }
        }
        if (totc == 0)
            break;
        for (int i = 1; i <= N; ++i) {
            if (id[i] == 0)
                id[i] = ++totc;
        }

        // 改边权
        N = totc;
        rt = id[rt];
        for (int i = 1; i <= tote; ++i) {
            int oriv = E[i].v;
            E[i].u = id[E[i].u];
            E[i].v = id[E[i].v];
            if (E[i].u != E[i].v)
                E[i].w -= in[oriv];
            else
                std::swap(E[i--], E[tote--]);
        }
    }

    return res;
}
