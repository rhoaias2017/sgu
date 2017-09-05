#include <iostream>
#include <vector>
#include <list>
#include <map>
#ifdef _MSC_VER
#include <hash_map>
using namespace stdext;
#define unordered_map hash_map
typedef __int64 longlong;
#else
#include <unordered_map>
typedef long long longlong;
#endif
#include <algorithm>
#include <string>
#include <memory>  
#include <cstring>
#include <queue>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#ifdef LOCAL_DEBUG
#define dprintf(...) printf (__VA_ARGS__)
#else
#define dprintf(...)
#endif

int L(int r) {return r * 2 + 1;}
int R(int r) {return r * 2 + 2;}

const int MAXN = 1000100;
struct Node { //[l, r]
  int l;
  int r;
  longlong sum; 
  longlong not_propagated;
  bool isLeaf() const {return l == r;}
};
Node nodes[MAXN + 1];

void init(int k, int l, int r) {
  nodes[k].l = l;
  nodes[k].r = r;
  nodes[k].sum = 0;
  nodes[k].not_propagated = 0;
  if (nodes[k].isLeaf()) return;
  int mid = (l + r) / 2;
  init(L(k), l, mid);
  init(R(k), mid + 1, r);
}

void update(int c, int l, int r, int diff) {
  Node& n = nodes[c];
  if (n.l == l && n.r == r) {
    n.not_propagated += diff;
    n.sum += diff * (r - l + 1);
    return;
  } 
  if (n.not_propagated) {
    nodes[L(c)].sum += n.not_propagated * (nodes[L(c)].r - nodes[L(c)].l + 1);
    nodes[L(c)].not_propagated += n.not_propagated;
    nodes[R(c)].sum += n.not_propagated * (nodes[R(c)].r - nodes[R(c)].l + 1);
    nodes[R(c)].not_propagated += n.not_propagated;
    n.not_propagated = 0;
  }
  if (nodes[L(c)].r >= r) {
    update(L(c), l, r, diff);
    n.sum += diff * max(r - max(l, nodes[L(c)].l) + 1, 0);
  } else if (nodes[R(c)].l <= l) {
    update(R(c), l, r, diff);
    n.sum += diff * max(min(r, nodes[R(c)].r) - l + 1, 0);
  } else {
    update(L(c), l, nodes[L(c)].r, diff);
    update(R(c), nodes[R(c)].l, r, diff);
    n.sum += diff * (r - l + 1);
  }
}

longlong query(int c, int l, int r) {
  Node& n = nodes[c];
  if (n.l == l && n.r == r) {
    return n.sum;
  } else if (n.isLeaf()) {
    return 0;
  }
  if (n.not_propagated) {
    nodes[L(c)].sum += n.not_propagated * (nodes[L(c)].r - nodes[L(c)].l + 1);
    nodes[L(c)].not_propagated += n.not_propagated;
    nodes[R(c)].sum += n.not_propagated * (nodes[R(c)].r - nodes[R(c)].l + 1);
    nodes[R(c)].not_propagated += n.not_propagated;
    n.not_propagated = 0;
  }
  if (nodes[L(c)].r >= r) {
    return query(L(c), l, r);
  } else if (nodes[R(c)].l <= l) {
    return query(R(c), l, r);
  }
  return query(L(c), l, nodes[L(c)].r) + query(R(c), nodes[R(c)].l, r);
}

int main() {
  int N, M;
  scanf("%d%d", &N, &M);
  init(0, 0, N - 1);
  for (int i = 0; i < N; ++i) {
    int k;
    scanf("%d", &k);
    update(0, i, i, k);
  }
  for (int i = 0; i < M; ++i) {
    char op;
    int a, b, c;
    scanf(" %c%d%d", &op, &a, &b);
    --a; --b;
    if (op == 'Q') {
      printf("%lld\n", query(0, a, b));
    } else if (op == 'C') {
      scanf("%d", &c);
      update(0, a, b, c);
    }
  }
  return 0;
}

