namespace TwoSAT
{

const int SIZE = MAXN << 1, SIZE_M = SIZE * SIZE;

int size;
int tote, head[SIZE], next[SIZE_M], to[SIZE_M];
bool mark[SIZE];
int st[SIZE], top;

inline void init(int n)
{
    size = n << 1;
    tote = 0;
    memset(head, 0, sizeof(head));
    memset(mark, 0, sizeof(mark));
}

inline void addEdge(int u, int v)
{
    to[++tote] = v;
    next[tote] = head[u]; head[u] = tote;
}

inline void addClause(int x, bool xv)
{
    x = (x - 1) << 1 | xv;
    addEdge(x ^ 1, x);
}

inline void addClause(int x, bool xv, int y, bool yv)
{
    x = (x - 1) << 1 | xv;
    y = (y - 1) << 1 | yv;
    addEdge(x ^ 1, y);
    addEdge(y ^ 1, x);
}

bool dfs(int u)
{
    if (mark[u^1])
        return false;
    if (mark[u])
        return true;

    mark[u] = true;
    st[++top] = u;
    for (int i = head[u]; i; i = next[i]) {
        if (!dfs(to[i]))
            return false;
    }
    return true;
}

bool exec()
{
    for (int i = 0; i < size; i += 2) {
        if (!mark[i] && !mark[i|1]) {
            top = 0;
            if (!dfs(i)) {
                for (; top > 0; --top) {
                    mark[st[top]] = false;
                }
                if (!dfs(i | 1))
                    return false;
            }
        }
    }
    return true;
}

}
