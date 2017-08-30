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
int r[MAXN + 1];
int bt[MAXN + 1];
int pt[MAXN + 1];
int prev[MAXN + 1];
struct edge {
  int w;
  int t;
  edge(int _t, int _w) : w(_w), t(_t) {}
};
struct V {
  int dist;
  int n;
  int s;
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
  priority_queue<int> pq;
  pq.push({0, s, s});
  while(!pq.empty()) {
    V v = pq.top();
    pq.pop();
    if (vis[v.n]) continue;
    vis[v.n] = true;
    dist[v.n] = v.dist;
    prev[v.n] = v.s;
    for (int i = 0; i < G[v.n].size(); ++i) {
      const edge& e = G[v.n][i];
      if (vis[e.t]) continue;
      int st = (bt[v.n] + (b[v.n] ? pt[v.n] : 0) +  - r[v.n] + v.dist) % (bt[v.n] + pt[v.n]); //time 0 - blue starts
      int tt = (bt[e.t] + (b[e.t] ? pt[e.t] : 0) +  - r[e.t] + v.dist) % (bt[e.t] + pt[e.t]);
      int wait = 0;
      if (st >= bt[v.n] && tt < bt[e.t] || st < bt[v.n] && tt >= bt[e.t]) {
        
      }
      pq.push({e.w + v.dist + wait, e.t, v.n});
    }
  }
}

int main() {
  int S, T;
  scanf("%d%d", &S, &T);
  S--; T--;
  int N, M;
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; ++i) {
    char c;
    scanf(" %c%d%d%d", &c, r + i, bt + i, pt + i);
    blue[i] = c == 'B' ? true : false;
  }
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--; v--;
  }
  dij(S);
  if (vis[T]) {
    printf("%d\n", dist[T]);
    vector<int> path;
    path.push_back(T);
    while (path.back() != S) {
      path.push_back(prev[path.back()]);
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); ++i) {
      printf("%d ", path[i] + 1);
    }
    printf("\n");
  } else {
    printf("0\n");
  }
  return 0;
}

