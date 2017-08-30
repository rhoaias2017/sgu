#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>  
#include <cstring>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
  if (a > b) return gcd(b, a);
  if (a == 0) return b;
  return gcd(b % a, a);
}

int main() {
  int count = 0;
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    if (gcd(i, N) == 1) count++;
  }
  cout << count << endl;
  return 0;
}

