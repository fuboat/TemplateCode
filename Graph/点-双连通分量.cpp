#include <vector>
#include <stack>
#include <iostream>
#define Pii pair<int, int>
using namespace std;
#define X first
#define Y second
#define MK(a, b) make_pair(a, b)
template <typename T> bool Chkmax(T &x, T y){ return x < y? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y){ return x > y? x = y, true : false; }

const int MAXN = 20000, MAXM = 400000;
int head[MAXN], to[MAXN], next[MAXN];

bool iscut[MAXN];
int bccid[MAXN];
vector<int> bcc[MAXN * 2];
int totbcc;
struct Tarjan{
	stack<Pii>st;
	int dfn[MAXN], low[MAXN];
	int dfs_clock;

	bool Dfs(int u, int fa)
	{
		int v, child(0);
		Pii E, S;
		low[u] = dfn[u] = ++ dfs_clock;
		
		for(int i = head[u]; i; i = next[i]){
			E = MK(u, v);
			v = to[i];
			if(!dfn[v]){
				child ++;
				st.push(E);
				Dfs(v, u);
				Chkmin(low[u], low[v]);
				if(low[v] < dfn[u]){
					totbcc ++;
					iscut[u] = true;
					while(!st.empty()){
						S = st.top();
						st.pop();
						if(Chkmax(bccid[S.X], totbcc))
							bcc[totbcc].push_back(S.X);
						if(Chkmax(bccid[S.Y], totbcc))
							bcc[totbcc].push_back(S.Y);
						if(S == E) break;
					}
				}
			}else if(dfn[v] < dfn[u] && u != fa){
				st.push(E);
				// Don't forget!
				Chkmin(low[u], dfn[v]);
			}
			
			if(fa == -1 && child < 2)
				iscut[u] = false;
		}
	}
};
