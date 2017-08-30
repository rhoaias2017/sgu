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
class Solution {
public:
    struct Node {
       int level;
       int pos;
       int v;
       Node(int n) {
          if (n == -1) {
            level = -1;
            return;
          }
          v = n % 10;
          n /= 10;
          pos = n % 10 - 1;
          n /= 10;
          level = n % 10;
          pos += (1 << (level - 1)) - 1;
          cout << pos << endl;
       }
    };
    int dfs(int cur, vector<Node>& nodes, int& path) {
      int ret =  0;
      int count = 0;
      int npath = 0;
      if (cur < 7) {
        if (nodes[cur * 2 + 1].level != -1) {
          count++;
          int lpath = 0;
          ret += dfs(cur * 2 + 1, nodes, npath);
          npath += lpath;
        }
        if (nodes[cur * 2 + 2].level != -1) {
          count++;
          ret += dfs(cur * 2 + 2, nodes, npath);
          int rpath = 0;
          npath += rpath;
        }
      }
      
      if (count == 0) npath = 1;
      ret += nodes[cur].v * npath;
      path += npath;
      return ret;
    }
    int pathSum(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<Node> tree(15, Node(-1));
        for (int i = 0; i < nums.size(); ++i) {
          Node n = Node(nums[i]);
          tree[n.pos] = n;
        }
      int p = 0;
      return dfs(0, tree, p);
    }
};

int main() {
  while (true) {
    int N;
    cin >> N;
    vector<int> v(N);
    for (int i = 0; i < N; ++i) cin >> v[i];
    cout << Solution().pathSum(v) << endl;
  }
  return 0;
}

