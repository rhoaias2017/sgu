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

const int MAXN = 200001;
void depth(vector<vector<int>>& G, int root, vector<bool>& vis,
         vector<int>& m1, vector<int>& m2, vector<int>& prime, vector<vector<int>>& f, map<int, int>& ret) {
  if (vis[root]) return; // visiting the parent
  vis[root] = true;
  vector<int> om1 = m1;
  vector<int> om2 = m2;
  for (int i = 0; i < prime.size(); ++i) {
    int fr = f[root][i];
    if (fr <= f[m1[i]][i]) {
      m2[i] = m1[i];
      m1[i] = root;
    } else if (fr <= f[m2[i]][i]) {
      m2[i] = root;
    }
  }
  
  int res = 1;
  for (int i = 0; i < prime.size(); ++i) {
    if (f[root][i] == 0) continue;
    res *= pow(prime[i], f[root][i]);
  }
  for (int i = 0; i < prime.size(); ++i) {
    if (f[m1[i]][i] == f[m2[i]][i]) continue;
    int tmp = 1;
    for (int j = 0; j < prime.size(); ++j) {
      int k;
      if (f[m1[i]][j] == f[m1[j]][j]) k = f[m2[j]][j];
      else k = f[m1[j]][j];
      tmp *= pow(prime[i], k);
    }
    res = max(tmp, res);
  }
  ret[root] = res;
  
  for (int i = 0; i < G[root].size(); ++i) {
    depth(G, G[root][i], vis, m1, m2, prime, f, ret);
  }
  m1.swap(om1);
  m2.swap(om2);
}

int main() {
  vector<bool> is_prime(MAXN, true);
  vector<int> prime;
  for (int i = 2; i <= MAXN; ++i) {
    if (is_prime[i]) {
      prime.push_back(i);
      for (int j = i * 2; j <= MAXN; j += i) {
        is_prime[j] = false;
      }
    }
  }
  
  int n;
  cin >> n;
  vector<int> a(n);
  vector<vector<int>> G(n);
  vector<vector<int>> f(n, vector<int>(0));
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    int tmp = a[i];
    for (int j = 0; j < prime.size(); ++j) {
      while (tmp % prime[j] != 0) {
        f[i][j]++;
        tmp /= prime[j];
      }
    }
  }
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    x--; y--;
    G[x].push_back(y);
    G[y].push_back(x);
  }
  vector<bool> vis(n, false);
  
  
  vector<int> m1(prime.size(), 0);
  vector<int> m2(prime.size(), 0);
  m1 = f[0];
  map<int, int> ret;
  ret[0] = a[0];
  for (int i = 0; i < G[0].size(); ++i) {
    m2 = f[G[0][i]];
    ret[G[0][i]] = max(a[0], a[G[0][i]]);
    for (int j = 0; j < G[G[0][i]].size(); ++j) {
      depth(G, G[G[0][i]][j], vis, m1, m2, prime, f, ret);
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << ret[i] << " ";
  }
  cout << endl;
  return 0;
}

