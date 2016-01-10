namespace TwoSAT
{

const int SIZE = MAXN << 1, SIZE_M = MAXM << 2;

int n;
int tote, head[SIZE], next[SIZE_M], to[SIZE_M];
int tote0, head0[SIZE], next0[SIZE_M], to0[SIZE_M];
int outdeg[SIZE];
int totscc, sccid[SIZE];
std::vector<int> scc[SIZE];
bool mark[SIZE], forbid[SIZE];

namespace Tarjan
{

int dfs_clock, dfn[SIZE], low[SIZE];
int st[SIZE], top;

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
        scc[totscc].clear();
        scc[totscc].push_back(u);
        for (; st[top] != u; --top) {
            sccid[st[top]] = totscc;
            scc[totscc].push_back(st[top]);
        }
        --top;
    }
}

void exec()
{
    dfs_clock = totscc = 0; // ERR#1: forgot "totscc"
    memset(dfn, 0, sizeof(dfn));
    memset(sccid, 0, sizeof(sccid));
    for (int i = 0; i < n; ++i) {
        if (dfn[i] == 0)
            dfs(i);
    }
}

}

inline void addEdge0(int u, int v)
{
    to0[++tote0] = v;
    next0[tote0] = head0[u]; head0[u] = tote0;
}

inline void addEdge(int u, int v)
{
    to[++tote] = v;
    next[tote] = head[u]; head[u] = tote;
    addEdge0(v, u);
}

inline void addClause(int x, bool xv, int y, bool yv)
{
    x = (x - 1) << 1 | xv;
    y = (y - 1) << 1 | yv;
    addEdge(x ^ 1, y);
    addEdge(y ^ 1, x);
}

void init(int sz)
{
    n = sz << 1;
    tote = tote0 = 0;
    memset(head, 0, sizeof(head));
    memset(head0, 0, sizeof(head0));
    memset(outdeg, 0, sizeof(outdeg));
    memset(mark, 0, sizeof(mark));
    memset(forbid, 0, sizeof(forbid));
}

inline void markscc(int x)
{
    const std::vector<int> &cur = scc[x];
    for (int i = 0; i < cur.size(); ++i) {
        mark[cur[i]] = true;
        forbid[sccid[cur[i]^1]] = true; // ERR#3: forgot "sccid"
    }
}

void markAll()
{
    static int q[SIZE];

    int front = 0, rear = 0;
    for (int i = 1; i <= totscc; ++i) {
        if (outdeg[i] == 0)
            q[rear++] = i;
    }
    while (front != rear) {
        int x = q[front++];
        if (!forbid[x])
            markscc(x);
        const std::vector<int> &cur = scc[x];
        for (int i = 0; i < cur.size(); ++i) {
            for (int j = head0[cur[i]]; j; j = next0[j]) { // ERR#2: "next" instead of "next0"
                int y = sccid[to0[j]];
                if (y != x) {
                    if (forbid[x])
                        forbid[y] = true;
                    if (--outdeg[y] == 0)
                        q[rear++] = y;
                }
            }
        }
    }
}

bool exec()
{
    Tarjan::exec();

    for (int i = 0; i < n; i += 2) {
        if (sccid[i] == sccid[i|1])
            return false;
    }

    for (int u = 1; u <= n; ++u) {
        for (int i = head[u]; i; i = next[i]) {
            int v = to[i];
            if (sccid[u] != sccid[v])
                ++outdeg[sccid[u]];
        }
    }

    markAll();

    return true;
}

}
