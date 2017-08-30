#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>  
#include <cstring>
#include <queue>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

const int MAXN = 50000;
int dist[MAXN + 1];
bool vis[MAXN + 1];
bool blue[MAXN + 1];
int bt[MAXN + 1];
int pt[MAXN + 1];
struct edge {
  int w;
  int t;
  edge(int _t, int _w) : w(_w), t(_t) {}
};
struct V {
  int dist;
  int n;
  bool operator<(const V& rhs) const {
    return rhs.n < n;
  }
};
vector<edge> G[MAXN + 1];

void add_edge(int u, int v, int w) {
  G[u].push_back(edge(v, w));
  G[v].push_back(edge(u, w));
}

void dij(int s) {
  priority_queue<int> pq;
  pq.push({0, s});
  while(!pq.empty()) {
    V v = pq.top();
    pq.pop();
    if (vis[v.n]) continue;
    vis[v.n] = true;
    dist[v.n] = v.dist;
    for (int i = 0; i < G[v.n].size(); ++i) {
      const edge& e = G[v.n][i];
      if (vis[e.t]) continue;
      pq.push({e.w + v.dist, e.t});
    }
  }
}

int main() {
  int S, T;
  scanf("%d%d", &S, &T);
  S--; T--;
  int N, M;
  scanf("%d%d", &N, &M);
  return 0;
}

