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
#include <cmath>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#ifdef LOCAL_DEBUG
#define dprintf(...) printf (__VA_ARGS__)
#else
#define dprintf(...)
#endif



long long gcd(long long a,long long b){
    if(b==0)return a;
    return gcd(b,a%b);
}
void _gcd(long long a,long long b,long long &x,long long &y){
    if(b==1){
        x=1;
        y=1-a;
    }
    else {
        long long x1,y1;
        _gcd(b,a%b,x1,y1);
        x=y1;
        y=x1-(a/b)*x;
    }
}
int main(){
    long long a,b,c,x1,x2,y1,y2;
    cin>>a>>b>>c>>x1>>x2>>y1>>y2;
        c=-c;
        if(c<0){
            a=-a;
            b=-b;
            c=-c;
        }
        if(a<0){
            a=-a;swap(x1,x2);
            x1=-x1;
            x2=-x2;
        }
        if(b<0){
            b=-b;swap(y1,y2);
            y2=-y2;
            y1=-y1;
        }//a<0,b<0,c<0时要分别作一下处理，因为扩展欧几里得中没有负数
        if(x1>x2||y1>y2){
            cout<<0<<endl;
            return 0;
        }
        if(!a||!b){
            if(!a&&!b){
                if(!c)
                cout<<(x2-x1+1)*(y2-y1+1)<<endl;
                else cout<<0<<endl;
            }
            if(!a&&b){
                if(c%b==0){
                    if(c/b-y1>=0&&c/b-y2<=0)
                    cout<<x2-x1+1<<endl;
                    else cout<<0<<endl;
                }
                else{
                    cout<<0<<endl;
                }
            }
            if(a&&!b){
                if(c%a==0){
                    if(c/a-x1>=0&&c/a-x2<=0)
                    cout<<y2-y1+1<<endl;
                    else cout<<0<<endl;
                }
                else{
                    cout<<0<<endl;
                }
            }
            return 0;
        }
        long long g=gcd(a,b);
        a/=g;
        b/=g;
        if(c%g!=0){
            cout<<0<<endl;
            return 0;
        }
        c/=g;
        long long x,y;
        _gcd(abs(a),abs(b),x,y);
        x=x*c;
        y=y*c;
//        cout<<y<<endl;
        long long sum1=floor((double)(x2-x)/(double)b);
        long long sum2=ceil((double)(x1-x)/(double)b);
        long long sum3=floor((double)(y-y1)/(double)(a));
        long long sum4=ceil((double)(y-y2)/(double)(a));
//        cout<<sum1<<" "<<sum2<<endl;
//        cout<<sum3<<" "<<sum4<<endl;
        if(min(sum1,sum3)-max(sum2,sum4)>=0)
        cout<<min(sum1,sum3)-max(sum2,sum4)+1<<endl;
        else cout<<0<<endl;
    return 0;
}