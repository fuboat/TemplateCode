int match[MAXN];

namespace Hungary
{

int rt;
int vis[MAXN];

bool dfs(int u)
{
    for (int v = 1; v <= N; ++v) {
        if (G[u][v] && vis[v] < rt) {
            vis[v] = rt;
            if (match[v] == 0 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int exec()
{
    int res = 0;
    memset(vis, 0, sizeof(vis));
    memset(match, 0, sizeof(match));
    for (rt = 1; rt <= N; ++rt) {
        if (color[rt] == 1 && dfs(rt))
            ++res;
    }
    return res;
}

}
