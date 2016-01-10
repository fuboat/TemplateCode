struct Edge {
    int u, v;
    int r;

    Edge() { }
    Edge(int u0, int v0, int r0): u(u0), v(v0), w(r0) { }
};

namespace Dinic
{

int dis[MAXN], cur[MAXN];

bool bfs()
{
    static int q[MAXN];

    int front = 0, rear = 0;
    memset(dis, 0, sizeof(dis));
    dis[1] = 1;
    q[rear++] = 1;
    while (front != rear) {
        int u = q[front++];
        for (int v = 1; v <= N; v++) {
            if (dis[v] == 0 && residual[u][v] > 0) {
                dis[v] = dis[u] + 1;
                q[rear++] = v;
            }
        }
    }

    return dis[N] > 0;
}

LL dfs(int u, LL a)
{
    if (u == N || a == 0)
        return a;

    LL res = 0, vf = 0;
    for (int &v = cur[u]; v <= N; v++) {
        if (dis[v] == dis[u] + 1 && (vf = dfs(v, std::min(a, residual[u][v])))) {
            residual[u][v] -= vf;
            residual[v][u] += vf;
            res += vf;
            if ((a -= vf) == 0)
                break;
        }
    }

    return res;
}

LL dinic()
{
    LL res = 0;
    memset(residual, 0, sizeof(residual));
    for (int i = 1; i <= M; i++) {
        residual[edge[i].u][edge[i].v] = capacity[edge[i].u][edge[i].v];
    }
    while (bfs()) {
        std::fill(cur + 1, cur + N + 1, 1);
        res += dfs(1, INT_MAX);
    }
    return res;
}

}