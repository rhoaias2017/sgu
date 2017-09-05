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


#define rep(i,n) for(int i = 0;i < n; i++)
using namespace std;
const int size  = 200005,INF = 1<<30;
int rk[size],sa[size],height[size],w[size],wa[size],res[size];//rk: 
void getSa (int len,int up) {
    int *k = rk,*id = height,*r = res, *cnt = wa;
    rep(i,up) cnt[i] = 0;
    rep(i,len) cnt[k[i] = w[i]]++;
    rep(i,up) cnt[i+1] += cnt[i];
    for(int i = len - 1; i >= 0; i--) {
        sa[--cnt[k[i]]] = i;
    }
    int d = 1,p = 0;
    while(p < len){
        for(int i = len - d; i < len; i++) id[p++] = i;
        rep(i,len)  if(sa[i] >= d) id[p++] = sa[i] - d;
        rep(i,len) r[i] = k[id[i]];
        rep(i,up) cnt[i] = 0;
        rep(i,len) cnt[r[i]]++;
        rep(i,up) cnt[i+1] += cnt[i];
        for(int i = len - 1; i >= 0; i--) {
            sa[--cnt[r[i]]] = id[i];
        } 
        swap(k,r);
        p = 0;
        k[sa[0]] = p++;
        rep(i,len-1) {
            if(sa[i]+d < len && sa[i+1]+d <len &&r[sa[i]] == r[sa[i+1]]&& r[sa[i]+d] == r[sa[i+1]+d])
                k[sa[i+1]] = p - 1;
            else k[sa[i+1]] = p++;
        }
        if(p >= len) return ;
        d *= 2,up = p, p = 0;
    }
}
void getHeight(int len) {
    rep(i,len) rk[sa[i]] = i;
    height[0] =  0;
    for(int i = 0,p = 0; i < len - 1; i++) {
        int j = sa[rk[i]-1];
        while(i+p < len&& j+p < len&& w[i+p] == w[j+p]) {
            p++;
        }
        height[rk[i]] = p;
        p = max(0,p - 1);
    }
}
int getSuffix(int s[], int len) {
    int up = 0; 
    for(int i = 0; i < len; i++) {
        w[i] = s[i];
        up = max(up,w[i]);
    }
    w[len++] = 0;
    getSa(len,up+1);
    getHeight(len);
    return len;
}

const int maxa = 100000*2+1;
int str[maxa];
int main(){
  while(true){
    int n;
    scanf("%d", &n);
    if (n == 0) break;
    for (int i = 0; i < n; ++i) {
      int k;
      scanf("%d", &k);
      str[i] = k;
    }
    if (n <= 4) {
      printf("0\n");
      continue;
    }
    for (int i = 0; i < n - 1; ++i) {
      str[i] = str[i + 1] - str[i] + 88; //make sure it's not zero.
    }
    str[n - 1] = 0;
    getSuffix(str, n - 1);
    int res = 0;
    int lo = 0;
    int hi = n - 2;
    while (lo <= hi) {
      int mid = (lo + hi) / 2;
      for (int i = 0; i <= n - 1; ++i) {
        //dprintf("height[%d] :  %d\n", i, height[i]);
        if (height[i] < mid) continue;
        int min_idx = min(sa[i - 1], sa[i]);
        int max_idx = max(sa[i - 1], sa[i]);
        ++i;
        while (i <= n - 1 && height[i] >= mid) {
          min_idx = min(min_idx, sa[i]);
          max_idx = max(max_idx, sa[i]);
          ++i;
        }
        if (max_idx - min_idx > mid) {
          res = max(mid, res);
          lo = mid + 1;
          break;
        }
      }
      if (lo != mid + 1) hi = mid - 1;
    }
    if (res < 4) res = 0;
    printf("%d\n", res + 1);
  }
}    