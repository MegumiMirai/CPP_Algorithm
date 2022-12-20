// 输入一串数字，给你 M 个询问，每次询问就给你两个数字 X,Y，要求你说出 X 到 Y 这段区间内的最大数。

// 输入格式
// 第一行两个整数 N,M 表示数字的个数和要询问的次数；

// 接下来一行为 N 个数；

// 接下来 M 行，每行都有两个整数 X,Y。

// 输出格式
// 输出共 M 行，每行输出一个数。

// 数据范围
// 1≤N≤105,
// 1≤M≤106,
// 1≤X≤Y≤N,
// 数列中的数字均不超过231−1
// 输入样例：
// 10 2
// 3 2 4 5 6 8 1 2 9 7
// 1 4
// 3 8
// 输出样例：
// 5
// 8

// 只是线段树的query从求和改变成了求最大值，其他都没变
// 还有，这道题必用scanf和printf，用cin和cout会TLE
#include<iostream>
#include<cstdio>
#include<climits>
using namespace std;

const int N = 1e5 + 10;
int w[N];
struct Node{
    int l, r, maxv;
}tr[N * 4];
int n, m;

void build(int u, int l, int r){
    if(l == r) tr[u] = {l, r, w[l]};
    else{
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l , mid), build(u << 1 | 1, mid + 1, r);
        tr[u].maxv = max(tr[u << 1].maxv, tr[u << 1 | 1].maxv);
    }
}

int query(int u, int l, int r){
    if(tr[u].l >= l && tr[u].r <= r) return tr[u].maxv;
    int mid = tr[u].l + tr[u].r >> 1;
    int res = INT_MIN;
    if(l <= mid) res = query(u << 1, l, r);
    if(r > mid) res = max(res, query(u << 1 | 1, l, r));
    return res;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    build(1, 1, n);
    
    int l, r;
    while(m--){
        scanf("%d%d", &l, &r);
        printf("%d\n", query(1, l, r));
    }
    
    return 0;
}