struct Network {
    int n, s, t;
    int totEdge, head[MAXN], next[MAXM], to[MAXM], id[MAXM];
    int cap[MAXM], flow[MAXM];
    int dis[MAXN], gap[MAXN];

    void init();
    void addEdge(int u, int v, int c, int i);
    void bfs(int s);
    int dfs(int u, int f);
    int maxFlow();
} G;

inline void Network::init()
{
    totEdge = 0;
    memset(head, -1, sizeof(head));
}

void Network::addEdge(int u, int v, int c, int i)
{
    to[totEdge] = v;
    cap[totEdge] = c;
    id[totEdge] = i;
    next[totEdge] = head[u]; head[u] = totEdge++;
    to[totEdge] = u;
    cap[totEdge] = 0;
    id[totEdge] = 0;
    next[totEdge] = head[v]; head[v] = totEdge++;
}

void Network::bfs(int s)
{
    static int Q[MAXN];
    int front = 0, rear = 0;
    memset(dis, -1, sizeof(dis));
    memset(gap, 0, sizeof(gap));

    Q[rear++] = s;
    dis[s] = 0; gap[0] = 1;
    while (front < rear) {
        int u = Q[front++];
        for (int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                gap[dis[v]]++;
                Q[rear++] = v;
            }
        }
    }
}

int Network::dfs(int u, int f)
{
    if (u == t)
        return f;

    int res = 0;
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (dis[v] + 1 == dis[u] && flow[i] < cap[i]) {
            int d = dfs(v, min(f - res, cap[i] - flow[i]));
            flow[i] += d; flow[i^1] -= d;
            res += d;

            if (res == f)
                return res;
        }
    }

    if (--gap[dis[u]] == 0)
        dis[s] = n;
    gap[++dis[u]]++;

    return res;
}

int Network::maxFlow()
{
    int res = 0;
    bfs(t);
    while (dis[s] < n)
        res += dfs(s, INF);
    return res;
}
