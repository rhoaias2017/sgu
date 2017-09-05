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

int s(int n) {
  int ret = 0;
  while (n) {
    ret += n % 10;
    n /= 10;
  }
  return ret;
}

const int M = 10000;
int d(int n, vector<int>& p) {
  int ret = n;
  while (n) {
    ret += p[n % M];
    n /= M;
  }
  return ret;
}

int main()
{
  int n,k,i,j,t,p,q,a[1000000];
  bool D[128],Dt[65];
  scanf("%d%d",&n,&k);
  t=0;
  memset(D,true,sizeof(D));
  for(i=1;i<=n;i+=64){
      memset(D+64,true,sizeof(D)/2);
      for(j=0;j<=63;++j){
	  p=q=j+i;
	  while(q){
	      p+=q%10;
	      q/=10;
	  }
	  D[p-i]=false;
      }
      for(p=0;p<=63;++p){
	  if(D[p]) a[++t]=i+p;
      }
      for(p=0;p<64;++p) D[p]=D[p+64];
  }
  while(a[t]>n) --t;
  printf("%d\n",t);
  for(i=0;i<k;i++){
      scanf("%d",&j);
      printf("%d ",a[j]);
  }
  printf("\n");
  return 0;
}