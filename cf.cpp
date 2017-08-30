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


int main() {
  long long r, d;
  cin >> r >> d;
  
  int n;
  cin >> n;
  int count = 0;
  for (int i = 0; i < n; ++i) {
    long long x;
    long long y;
    long long R;
    cin >> x >> y >> R;
    long long lo = (r - d) * (r - d);
    long long hi = r * r;
    long long pos = x * x + y * y;
    long long lor = (r - d + R) * (r - d + R);
    long long hir = (r - R) * (r - R);
    if (pos >= lo && pos <= hi && R <= d && pos <= hir && pos >= lor) {
      count++;
    }
  }
  cout << count << endl;
  return 0;
}

