int totscc;
int sccid[MAXN];

namespace Tarjan {

int dfs_clock, dfn[MAXN], low[MAXN];
int st[MAXN];
int top;

void dfs(int u)
{
    low[u] = dfn[u] = ++dfs_clock;
    st[++top] = u;

    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (dfn[v] == 0) {
            dfs(v);
            chkmin(low[u], low[v]);
        } else if (sccid[v] == 0)
            chkmin(low[u], dfn[v]);
    }

    if (low[u] == dfn[u]) {
        sccid[u] = ++totscc;
        for (; st[top] != u; --top) {
            sccid[st[top]] = totscc;
        }
        --top;
    }
}

void exec()
{
    dfs_clock = totscc = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(sccid, 0, sizeof(sccid));
    for (int i = 1; i <= N; ++i) {
        if (dfn[i] == 0)
            dfs(i);
    }
}

}

