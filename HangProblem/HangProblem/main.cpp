#include<iostream>
#include<map>
#include<string>
#include<string.h>
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
map<string, int>p;
vector<int>v;
queue<int>q;
int n, m, cnt = -1, head[606], d[606], a[606], pre_e[606];
bool vis[606];   //标志数组
string s[105];
struct edge {
	int from, to, cap, dis, nxt, flow;
}e[605 << 3];
inline void addedge(int from, int to, int cap, int dist) {
	e[++cnt] = edge { from, to, cap, dist, head[from], cap };
	head[from] = cnt;
	e[++cnt] = edge{ to, from, 0, -dist, head[to], 0 };
	head[to] = cnt;
}
bool spfa(int s, int t, int& flow, int& cost) {
	memset(a, 0x3f, sizeof a);
	memset(pre_e, -1, sizeof a);
	memset(vis, 0, sizeof vis);
	for (int i = 0; i <= 605; ++i)d[i] = -2000000;
	d[s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = head[u]; i != -1; i = e[i].nxt)
			if (e[i].cap&&d[e[i].to]<d[u] + e[i].dis) {
				d[e[i].to] = d[u] + e[i].dis;
				pre_e[e[i].to] = i;
				a[e[i].to] = (a[u]>e[i].cap) ? e[i].cap : a[u];
				if (!vis[e[i].to]) {
					vis[e[i].to] = 1;
					q.push(e[i].to);
				}
			}
	}
	if (d[t] <= -2000000)return 0;
	flow += a[t];
	cost += d[t] * a[t];
	for (int i = t; i != s; i = e[pre_e[i]].from) {
		e[pre_e[i]].cap -= a[t];
		e[pre_e[i] ^ 1].cap += a[t];
	}
	return 1;
}
int maxflow(int s, int t, int& cost) {
	int flow = 0;
	cost = 0;
	while (spfa(s, t, flow, cost));
	return flow;
}
void find(int now) {
	if (now <= n)v.push_back(now);
	for (int i = head[now]; i != -1; i = e[i].nxt)
		if (e[i].cap<e[i].flow&&e[i].flow) {
			find(e[i].to);
			++e[i].cap;
			break;
		}
}
int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	memset(head, -1, sizeof head);
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		p[s[i]] = i;
	}
	for (int i = 2; i<n; ++i)addedge(i, i + n, 1, 0);
	addedge(1, n + 1, 2, 0); addedge(n, n << 1, 2, 0);
	for (; m--;) {
		string u, v;
		cin >> u >> v;
		int a = p[u], b = p[v];
		if (a>b)a ^= b ^= a ^= b;
		if (a == 1 && b == n)addedge(n + 1, n, 2, 1); else
			addedge(a + n, b, 1, 1);
	}
	int cost;
	if (maxflow(1, n << 1, cost) != 2)return!printf("No Solution!");
	cout << cost << endl;
	find(1);
	for (int i = 0, sz = v.size(); i<sz; ++i)cout << s[v[i]] << endl;
	v.clear();
	find(1);
	for (int i = v.size() - 2; i >= 0; --i)cout << s[v[i]] << endl;
	return 0;
}