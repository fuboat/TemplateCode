int totbcc;
int bccid[MAXN];
bool iscut[MAXN];
std::vector<int> bcc[MAXN];

namespace Tarjan {

int dfs_clock, dfn[MAXN], low[MAXN];
std::pair<int, int> st[MAXN];
int top;

void dfs(int u, int fa)
{
	low[u] = dfn[u] = ++dfs_clock;
	int tot_child = 0;
	for (int i = head[u]; i; i = next[i]) {
		int v = to[i];
		std::pair<int, int> cur = std::make_pair(u, v);

		if (dfn[v] == 0) {
            ++tot_child;
            st[++top] = cur;
			dfs(v, u);
            chkmin(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                iscut[u] = true;
                bcc[++totbcc].clear();
                for (;;) {
                    std::pair<int, int> x = st[top--];
                    if (chkmax(bccid[x.first], totbcc))
                        bcc[totbcc].push_back(x.first);
                    if (chkmax(bccid[x.second], totbcc))
                        bcc[totbcc].push_back(x.second);
                    if (x == cur)
                        break;
                }
            }
		} else if (dfn[v] < dfn[u] && v != fa) {
            st[++top] = cur;
            chkmin(low[u], dfn[v]);
		}
	}

	if (fa == 0 && tot_child < 2)
        iscut[u] = false;
}

void exec()
{
    dfs_clock = totbcc = 0;
	memset(dfn, 0, sizeof(dfn));
    memset(bccid, 0, sizeof(bccid));
	memset(iscut, 0, sizeof(iscut));
	for (int i = 1; i <= N; ++i) {
		if (dfn[i] == 0)
            dfs(i, 0);
    }
}

}
