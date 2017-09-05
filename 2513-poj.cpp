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

const int MAXN = 500000;
int s[MAXN];
int c[MAXN];

int find_set(int x) {
  if (s[x] != x) {
    s[x] = find_set(s[x]);
  }
  return s[x];
}

int union_set(int x, int y) {
  int rx = find_set(x);
  int ry = find_set(y);
  s[rx] = ry;
  c[ry] += c[rx] + 1;
  return ry;
}

int main() {
  memset(s, 0, MAXN);
  memset(c, 0, MAXN);
  for (int i = 0; i < MAXN; ++i) s[i] = i;
  char c1[20];
  char c2[20];
  unordered_map<string, int> s2i;
  vector<int> d;
  while (scanf("%s%s", c1, c2) != EOF) {
    if (s2i.find(c1) == s2i.end()) {
      s2i[c1] = d.size();
      d.push_back(0);
    }
    if (s2i.find(c2) == s2i.end()) {
      s2i[c2] = d.size();
      d.push_back(0);
    }
    int d1 = s2i[c1];
    int d2 = s2i[c2];
    d[d1]++;
    d[d2]++;
    int r1 = find_set(d1);
    int r2 = find_set(d2);
    
    if (r1 != r2) union_set(r1, r2);
  }
  int odd = 0;
  for (int i = 0; i < d.size(); ++i) {
    if (d[i] % 2) odd++;
  }
  if (odd > 2) {
    printf("Impossible\n");
  } else {
    if (d.size() == 0 || c[find_set(0)] + 1 == d.size()) {
      printf("Possible\n");
    } else {
      printf("Impossible\n");
    }
  }
  return 0;
}

