int dis[MAXN];

namespace Dijkstra
{

int heap_size;
int pos[MAXN];
std::pair<int, int> heap[MAXN];

void heapify(int u)
{
    std::pair<int, int> x = heap[u];
    for (int v = u << 1; v <= heap_size; u = v, v <<= 1) {
        if ((v | 1) <= heap_size && heap[v|1].first < heap[v].first)
            v |= 1;
        if (x.first > heap[v].first) {
            heap[u] = heap[v];
            pos[heap[u].second] = u;
        } else
            break;
    }
    heap[u] = x;
    pos[heap[u].second] = u;
}

void insert(std::pair<int, int> x)
{
    if (pos[x.second] == 0)
        pos[x.second] = ++heap_size;
    int u = pos[x.second];
    heap[u] = x;
    for (; u > 1 && heap[u].first < heap[u>>1].first; u >>= 1) {
        std::swap(heap[u], heap[u>>1]);
        std::swap(pos[heap[u].second], pos[heap[u>>1].second]);
    }
}

std::pair<int, int> extract()
{
    std::pair<int, int> x = heap[1];
    pos[heap[1].second] = 0;
    heap[1] = heap[heap_size];
    if (--heap_size > 0) {
        pos[heap[1].second] = 1;
        heapify(1);
    }
    return x;
}

void exec(int s)
{
    memset(pos, 0, sizeof(pos));
    for (int i = 1; i <= N; ++i) {
        dis[i] = INT_MAX;
    }

    dis[s] = 0;
    insert(std::make_pair(0, s));
    while (heap_size > 0) {
        int u = extract().second;
        for (int i = head[u]; i; i = next[i]) {
            int v = to[i];
            if (chkmin(dis[v], dis[u] + weight[i]))
                insert(std::make_pair(dis[v], v));
        }
    }
}

}
