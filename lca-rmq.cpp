#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>  
#include <cstring>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

const int MAXN = 40000;

struct edge {
  int to;
  int w;
  edge(int _to, int _w) : to(_to), w(_w) {}
};

int dist[MAXN + 1];
vector<edge> G[MAXN + 1]; //adjancent list
int vs[MAXN * 2 + 1];
bool vis[MAXN + 1];
int dep[MAXN + 1];
int first[MAXN + 1];//first time appearance in dfs result.
int rmq[MAXN * 2 + 1][17];

int k = 0;
void dfs(int v, int d, int p, int dis) {
  if (vis[v]) return;
  vis[v] = true;
  first[v] = k;
  dist[v] = dis;
  vs[k++] = v;
  dep[v] = d;
  for (int i = 0; i < G[v].size(); ++i) {
    if (G[v][i].to == p) continue;
    dfs(G[v][i].to, d + 1, v, dis + G[v][i].w);
    vs[k++] = v;
  }
}

void add_edge(int v, int u, int w) {
  G[v].push_back(edge(u, w));
  G[u].push_back(edge(v, w));
}

int smaller_depth_idx(int i, int j) {
  return dep[i] < dep[j] ? i : j;
}
void init_rmq() {
  for (int i = 0; i < k; ++i) {
    rmq[i][0] = vs[i];
  }
  for (int i = 1; i < 17; ++i) {
    for (int j = 0; j < k; ++j) {
      if (j + (1 << i) <= k) {
        rmq[j][i] = smaller_depth_idx(rmq[j][i - 1], rmq[j + (1 << (i - 1))][i - 1]);
      }
    }
  }
}

int rmq_query(int a, int b) { //[a, b)
  int k = 0;
  while ((1 << (k + 1)) < b - a) ++k;
  return smaller_depth_idx(rmq[a][k], rmq[b - (1 << k)][k]);
}

int LCA(int a, int b) {
  if (first[a] > first[b]) swap(a, b);
  return rmq_query(first[a], first[b] + 1);
}

int main() {
  int V, E;
  scanf("%d %d", &V, &E);
  int u, v, w;
  char r;

  for (int i = 0; i < E; ++i)
  {
      scanf("%d%d%d %c", &u, &v, &w, &r);
      --u, --v;
      add_edge(u, v, w);
  }
  for (int i = 0; i < V; ++i) dfs(i, 0, -1, 0);
  init_rmq();
  int K;
  scanf("%d", &K);
  for (int i = 0; i < K; ++i)
  {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      int t = LCA(u, v);
      int ans = dist[u] - dist[t] + dist[v] - dist[t];
      printf("%d\n", ans);
  }
  return 0;
}

