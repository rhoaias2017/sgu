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

vector<vector<int>> G(120000);
vector<int> BIT;
int cnt = 0;
vector<int> first(120000, -1);
vector<int> last(120000, -1);
vector<bool> visited(120000, false);

void dfs(int cur) {
  if (visited[cur]) return;
  visited[cur] = true;
  
  first[cur] = ++cnt;
  
  for (int i = 0; i < G[cur].size(); ++i) {
    dfs(G[cur][i]);
  }
  
  last[cur] = cnt;
}

int lowbit(int x) {
  return x & (-x);
}

void update(int x, int v) {
  for (int i = x; i < BIT.size(); i += lowbit(i)) {
    BIT[i] += v;
  }
}

void init(int n) {
  BIT = vector<int>(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    update(i, 1);
  }
}

int query(int k) {
  int ret = 0;
  for (int i = k; i > 0; i -= lowbit(i)) {
    ret += BIT[i];
  }
  return ret;
}

int main() {
  int N;
  scanf("%d", &N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  int M;
  scanf("%d", &M);
  vector<bool> has(N + 1, true);
  dfs(1);
  init(N);
  for (int i = 0; i < M; ++i) {
    char c;
    int x;
    scanf(" %c%d", &c, &x);
    if (c == 'C') {
      if (has[x]) update(first[x], -1); //update with diff
      else update(first[x], 1);
      has[x] = !has[x];
    } else {
      
      printf("%d\n",query(last[x]) - query(first[x] - 1));
    }
  }
  return 0;
}

