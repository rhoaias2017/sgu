#include <iostream>
#include <vector>
#include <list>
#include <map>
#ifdef _MSC_VER
#include <hash_map>
using namespace stdext;
#define unordered_map hash_map
#else
#include <unordered_map>
#endif
#include <algorithm>
#include <string>
#include <memory>  
#include <cstring>
#include <queue>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

const int MAXN = 50000;
int dist[MAXN + 1][2];
int vis[MAXN + 1];

struct edge {
  int w;
  int t;
  edge(int _t, int _w) : w(_w), t(_t) {}
};
struct V {
  int dist;
  int n;
  V(int _dist, int _n) : dist(_dist), n(_n) {}
  bool operator<(const V& rhs) const {
    return rhs.dist < dist;
  }
};
vector<edge> G[MAXN + 1];

void add_edge(int u, int v, int w) {
  G[u].push_back(edge(v, w));
  G[v].push_back(edge(u, w));
}

void dij(int s) {
  priority_queue<V> pq;
  pq.push(V(0, s));
  while(!pq.empty()) {
    V v = pq.top();
    pq.pop();
    if (vis[v.n] == 1) {
      if (dist[v.n][0] == v.dist) continue;
    } else if (vis[v.n] >= 2) {
      if (v.dist == dist[v.n][0] || v.dist >= dist[v.n][1]) continue;
    }
    vis[v.n]++;
    if (vis[v.n] == 1) dist[v.n][0] = v.dist;
    else  dist[v.n][1] = v.dist;
    if (vis[v.n] >= 2 && dist[v.n][0] > dist[v.n][1]) swap(dist[v.n][0], dist[v.n][1]);
    
    for (int i = 0; i < G[v.n].size(); ++i) {
      const edge& e = G[v.n][i];
      pq.push(V(e.w + v.dist, e.t));
    }
  }
}

int main() {
  int N, R;
  scanf("%d%d", &N, &R);
  for (int i = 0; i < R; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--;
    v--;
    add_edge(u, v, w);
  }
  dij(0);
  cout << dist[N - 1][1] << endl;
  return 0;
}

