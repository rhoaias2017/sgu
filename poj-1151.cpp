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

#ifdef LOCAL_DEBUG
#define dprintf(...) printf (__VA_ARGS__)
#else
#define dprintf(...)
#endif

struct Line {
  Line(double _x, double _y1, double _y2, int _event)
    : x(_x), y1(_y1), y2(_y2), event(_event) { }
  double x;
  double y1;
  double y2;
  int event; // 1 = in 2 = out 12121212121212
  bool operator<(const Line& rhs) const {
    return x < rhs.x;
  }
};

int L(int r) {return r * 2 + 1;}
int R(int r) {return r * 2 + 2;}

const int MAXN = 1000;
struct Node { //[l, r]
  int l;
  int r;
  double len; //actual length covered
  int cover; //how many times being covered
  bool isLeaf() const {return l + 1 == r;}
};
int N;
Node nodes[MAXN + 1];
double y[MAXN * 2 + 1];

void init(int k, int l, int r) {
  nodes[k].l = l;
  nodes[k].r = r;
  nodes[k].len = 0;
  nodes[k].cover = 0;
  if (nodes[k].isLeaf()) return;
  int mid = (l + r) / 2;
  init(L(k), l, mid);
  init(R(k), mid, r);
}

void update_length(int c) {
  Node& n = nodes[c];
  if (n.cover) {
    n.len = y[n.r] - y[n.l];
  } else if (!n.isLeaf()) {
    n.len = nodes[L(c)].len + nodes[R(c)].len;
  } else { //leaf and not covered. this will bubble up so parents will get updated.
    n.len = 0;
  }
  dprintf("%d: [%d, %d] [%lf, %lf] %lf\n", c, n.l, n.r, y[n.l], y[n.r], n.len);
}

void update(int c, const Line& line) {
  Node& n = nodes[c];
  if (y[n.l] == line.y1 && y[n.r] == line.y2) {
    n.cover += line.event;
  } else if (y[nodes[L(c)].r] >= line.y2) {
    update(L(c), line);
  } else if (y[nodes[R(c)].l] <= line.y1) {
    update(R(c), line);
  } else {
    update(L(c), Line(line.x, line.y1, y[nodes[L(c)].r], line.event));
    update(R(c), Line(line.x, y[nodes[R(c)].l], line.y2, line.event));
  }
  update_length(c);
}

int main() {
  int count = 0;
  while (true) {
    scanf("%d", &N);
    count++;
    if (N == 0) break;
    vector<Line> lines;
    for (int i = 0; i < N; ++i) {
      double x1, x2, y1, y2;
      scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
      lines.push_back(Line(x1, y1, y2, 1));
      lines.push_back(Line(x2, y1, y2, -1));
      y[i * 2] = y1;
      y[i * 2 + 1] = y2;
    }
    sort(lines.begin(), lines.end());
    sort(y, y + 2 * N);
    init(0, 0, 2 * N - 1);
    double res = 0;
    for (int i = 0; i < lines.size(); ++i) {
      if (i > 0) res += (lines[i].x - lines[i - 1].x) * nodes[0].len;
      update(0, lines[i]);
      dprintf("=======================\n");
    }
    printf("Test case #%d\nTotal explored area: %.2lf\n\n", count, res);
  }
  
  return 0;
}

