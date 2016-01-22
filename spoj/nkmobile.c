#include<iostream>
#include<cstdio>
#include<algorithm>
#define lowbit(x)x&(-x)
using namespace std;

const int MAXS = 1025;
int S,cmd,ans;
int X,Y,A,L,B,R,T;
int tree[MAXS][MAXS];

void inc(int r,int c,int val){
    for(int i = r;i <= S;i+=lowbit(i))
        for(int j = c;j <= S;j+=lowbit(j)) {
            tree[i][j]+=val;
	}
}

long long sum(int r,int c){
    int ret = 0;
    for(int i = r;i > 0;i-=lowbit(i))
        for(int j = c;j > 0;j-=lowbit(j))
            ret+=tree[i][j];
    return ret;
}

long long sum(int r1,int c1,int r2,int c2){
    return sum(r2,c2)-sum(r1-1,c2)-sum(r2,c1-1)+sum(r1-1,c1-1);
}

int main(){
    scanf("%d%d",&cmd,&S);
    while(scanf("%d",&cmd) && cmd != 3){
        if(cmd == 1){
            scanf("%d%d%d",&X,&Y,&A);X++,Y++;
            inc(X,Y,A);
        }
        if(cmd == 2){
            scanf("%d%d%d%d",&L,&B,&R,&T);L++,B++,R++,T++;
            printf("%lld\n",sum(L,B,R,T));
        }
    }
    return 0;
}
