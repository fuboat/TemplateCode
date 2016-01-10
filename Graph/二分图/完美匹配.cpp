template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int oo = 0x3f3f3f3f;
int next[MAXM], val[MAXM], to[MAXM];
int S[MAXN], T[MAXN], slack[MAXN], head[MAXN];
int cur;
bool Match(int u)
{
	int v, w, t;
	S[u] = cur;
	for(int i = head[u]; i; i = next[i]){
		v = to[i], w = val[i];
		if(T[v] == cur) continue;
		t = Lx[u] + Ly[v] - w;
		
		if(t > 0) Chkmin(slack[v], t);
		else{
			T[v] = cur;
			if(!link[v] || Match(link[v]){
				link[v] = u;
				return true;
			}
		}
	}
}
void Update()
{
	int a = oo;
	REP(i, 1, n) if(T[i] != cur)
		Chkmin(a, slack[i]);
	REP(i, 1, n)
		if(S[i] == cur)
			Lx[i] -= a;
	REP(i, 1, n)
		if(T[i] == cur)
			Ly[i] += a;
		else slack[i] -= a;
	
}
int main()
{
	int w;
	REP(u, 1, n){
		Lx[u] = 0;
		for(int i = head[u]; i; i = next[i])
			Chkmax(Lx[u], val[i]);
	}
	REP(i, 1, n){
		
	}
}
