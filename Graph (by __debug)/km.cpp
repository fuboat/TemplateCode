int match[MAXN];

namespace KM {

int cur;
int fx[MAXN], fy[MAXN];
int lx[MAXN], ly[MAXN], slack[MAXN];

bool dfs(int u)
{
    fx[u] = cur;
    for (int v = 1; v <= N; ++v) {
        if (fy[v] == cur)
            continue;
        int t = lx[u] + ly[v] - G[u][v];
        if (t > 0)
            chkmin(slack[v], t);
        else {
            fy[v] = cur;
            if (match[v] == 0 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void update()
{
    int a = oo;
    for (int i = 1; i <= N; ++i) {
        if (fy[i] < cur)
            chkmin(a, slack[i]);
    }
    for (int i = 1; i <= N; ++i) {
        if (fx[i] == cur)
            lx[i] -= a;
    }
    for (int i = 1; i <= N; ++i) {
        if (fy[i] == cur)
            ly[i] += a;
        else
            slack[i] -= a;
    }
}

void exec()
{
    cur = 0;
    memset(fx, 0, sizeof(fx));
    memset(fy, 0, sizeof(fy));
    memset(ly, 0, sizeof(ly));
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= N; ++i) {
        lx[i] = *std::max_element(G[i] + 1, G[i] + N + 1);
    }
    for (int i = 1; i <= N; ++i) {
        memset(slack, oo, sizeof(slack));
        for (++cur; !dfs(i); ++cur) {
            update();
        }
    }
}

}
