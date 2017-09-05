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

int main ()
{
    int n; scanf("%d", &n);
    if(n < 9) return printf("0\n"), 0;
    else if(n ==9 ) return printf("8\n"), 0;
    else{
        printf("72");
        n -= 10;
        while(n){printf("0");n--;}
        printf("\n");
    }
    return 0;
}