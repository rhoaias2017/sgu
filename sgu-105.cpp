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

int main() {
  int N;
  cin >> N;
  if (N % 3 == 0) {
    cout << N / 3 * 2 << endl;
  } else if (N % 3 == 1) {
    cout << (N - 1) / 3 * 2 << endl;
  } else {
    cout << (N - 2) / 3 * 2 + 1 << endl;
  }
  return 0;
}

