// 给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环， 边权可能为负数。

// 请你求出 1 号点到 n 号点的最短距离，如果无法从 1 号点走到 n 号点，则输出 impossible。

// 数据保证不存在负权回路。

// 输入格式
// 第一行包含整数 n 和 m。

// 接下来 m 行每行包含三个整数 x,y,z，表示存在一条从点 x 到点 y 的有向边，边长为 z。

// 输出格式
// 输出一个整数，表示 1 号点到 n 号点的最短距离。

// 如果路径不存在，则输出 impossible。

// 数据范围
// 1≤n,m≤105,
// 图中涉及边长绝对值均不超过 10000。

// 输入样例：
// 3 3
// 1 2 5
// 2 3 -3
// 1 3 4
// 输出样例：
// 2

// spfa是在bellman-ford的基础上进行了优化，它的优化是将某个点的dist变小之后将它存进队列只对队列里面的元素进行操作
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int N = 100010;
int e[N], ne[N], w[N], h[N], idx; // w数组保存权重
bool st[N];
int dist[N];
queue<int> q;
int n, m;

void add(int a, int b, int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void spfa(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    q.push(1);
    st[1] = true;
    while(q.size()){
        int t = q.front();
        q.pop();
        st[t] = false; // 从队列中删除该元素
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(dist[j] > dist[t] + w[i]){ 
                dist[j] = dist[t] + w[i];
                if(!st[j]){
                    q.push(j);
                    st[j] = true; // 表示队列中存在这个元素
                }
            }
        }
    }
}

int main(){
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    spfa();
    if(dist[n] == 0x3f3f3f3f) cout << "impossible" << endl;
    else cout << dist[n] << endl;
    return 0;
}