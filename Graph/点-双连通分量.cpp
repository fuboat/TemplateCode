#define pii pair<int, int>
template <typename T> bool Chkmax(int &x, int y){ return x < y? x = y, true : false; }
template <typename T> bool Chkmin(int &x, int y){ return x > y? x = y, true : false; }

const int MAXN = 20000, MAXM = 400000;
int head[MAXN], to[MAXN], next[MAXN];

bool iscut[MAXN], bccid[MAXN];
struct Tarjan{
	pii st[MAXM];
	int top;
	int pre[MAXN];

	bool Dfs(int u){}
};
