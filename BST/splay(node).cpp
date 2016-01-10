#include <cstdio>
#include <iostream>
#include <algorithm>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(register int i = x; i >= y; i --)
const int MAXN = 30000 + 1000;
int a[MAXN], ans[MAXN], que[MAXN];
struct node{
	node *son[2], *fa;
	int sum, val;
	inline void Maintain(){ sum = son[0]->sum + son[1]->sum + 1; }
	void Rotate()
	{
		node *pa, *up, *c;
		pa = fa;
		up = pa->fa;
		bool d = (pa->son[1] == this);
		c = son[!d];
		(this->fa = up)->son[up->son[1] == pa] = this;
		(c->fa = pa)->son[d] = c;
		(pa->fa = this)->son[!d] = pa;
		pa->Maintain();
		Maintain();
	}
};

struct Splay_tree{
	node *null, *root;
	node *space[MAXN];
	int sz;
	void Init(int n)
	{
		null = new node;
		null->fa = null;
		null->fa = null->son[1] = null->son[0] = null;
		root = null;
		REP(i, 1, n){
			space[i] = new node;
			node* tmp = space[i];
			tmp->fa = tmp->son[0] = tmp->son[1] = null;
		}
	}
	void Splay(node *o, node *F)
	{
		node *pa, *up;
		if(o == null) return ;
		while(o->fa != F){
			pa = o->fa, up = pa->fa;
			if(up == F){ o->Rotate(); break; }
			else if((up->son[0] == pa) ^ (pa->son[0] == o))
				pa->Rotate(), o->Rotate();
			else o->Rotate(), o->Rotate();
		}
		if(F == null) root = o;
		o->Maintain();
	}
	void Insert(int x)
	{
		node *o;
		sz ++;
		if(root == null){
			root = space[sz];
		}else{
			o = root;
			bool d = (x > o->val);
			while(o->son[d] != null){
				o = o->son[d];
				d = (x > o->val);
			}
			o->son[d] = space[sz];
			space[sz]->fa = o;
		}
		o = space[sz];
		o->val = x;
		Splay(o, null);
	}
	int Query(int k)
	{
		node *o = root;
		while(o->son[0]->sum + 1 != k){
			if(k <= o->son[0]->sum) o = o->son[0];
			else{ k -= o->son[0]->sum + 1; o = o->son[1]; }
		}
		Splay(o, null);
		return o->val;
	}
}t;
int n, m;
int readin()
{
	int x = 0;
	bool flag = 0;
	char c = 0;
	while(c = getchar()){
		if(c == '-') return -readin();
		else if('0' <= c && c <= '9'){
			(x *= 10) += c - '0';
			flag = true;
		}else if(flag) return x;
	}
	return x;
}
void Init()
{
	scanf("%d%d", &n, &m);
	REP(i, 1, n) a[i] = readin();
	REP(i, 1, m) que[i] = readin();
}
void Write(int x)
{
	if(x == 0){
		putchar('0');
		putchar('\n');
		return ;
	}else if(x < 0){
		putchar('-');
		x = -x;
	}
	char c[70];
	int cnt = 0;
	while(x){
		c[cnt ++] = x % 10 + '0';
		x /= 10;
	}
	rep(i, cnt - 1, 0) putchar(c[i]);
	putchar('\n');
}
void Solve()
{
	int head = 0, x, pos;
	int cnt = 1;
	t.Init(n);
	REP(i, 1, n){
		t.Insert(a[i]);
		while(cnt <= n && que[cnt] == i){
			Write(t.Query(cnt));
			cnt ++;
		}
	}
}
int main()
{
	Init();
	Solve();
}
