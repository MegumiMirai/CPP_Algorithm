// 你现在被困在一个三维地牢中，需要找到最快脱离的出路！

// 地牢由若干个单位立方体组成，其中部分不含岩石障碍可以直接通过，部分包含岩石障碍无法通过。

// 向北，向南，向东，向西，向上或向下移动一个单元距离均需要一分钟。

// 你不能沿对角线移动，迷宫边界都是坚硬的岩石，你不能走出边界范围。

// 请问，你有可能逃脱吗？

// 如果可以，需要多长时间？

// 输入格式
// 输入包含多组测试数据。

// 每组数据第一行包含三个整数 L,R,C 分别表示地牢层数，以及每一层地牢的行数和列数。

// 接下来是 L 个 R 行 C 列的字符矩阵，用来表示每一层地牢的具体状况。

// 每个字符用来描述一个地牢单元的具体状况。

// 其中, 充满岩石障碍的单元格用”#”表示，不含障碍的空单元格用”.”表示，你的起始位置用”S”表示，终点用”E”表示。

// 每一个字符矩阵后面都会包含一个空行。

// 当输入一行为”0 0 0”时，表示输入终止。

// 输出格式
// 每组数据输出一个结果，每个结果占一行。

// 如果能够逃脱地牢，则输出”Escaped in x minute(s).”，其中X为逃脱所需最短时间。

// 如果不能逃脱地牢，则输出”Trapped!”。

// 数据范围
// 1≤L,R,C≤100
// 输入样例：
// 3 4 5
// S....
// .###.
// .##..
// ###.#

// #####
// #####
// ##.##
// ##...

// #####
// #####
// #.###
// ####E

// 1 3 3
// S##
// #E#
// ###

// 0 0 0
// 输出样例：
// Escaped in 11 minute(s).
// Trapped!

// 我自己写得代码
// 只是二维变三维，但是这道题最好还是按照 (z, x, y)这个坐标来保存比较好，这个坐标搞得我头都大了
// 但是好像是我坐标列错了，我这么搞很麻烦，想的有点太多了
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int N = 110;
char g[N][N][N];
int dist[N][N][N];
struct Node{
    int z, x, y;
};
int l, r, c;

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, -1, 1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};
int bfs(Node start, Node end){
    memset(dist, -1, sizeof(dist));
    queue<Node> q;
    dist[start.z][start.x][start.y] = 0;
    q.push(start);
    while(q.size()){
        auto t = q.front();
        q.pop();
        int z = t.z, x = t.x, y = t.y;
        for(int i = 0; i < 6; i++){
            int a = z + dz[i], b = x + dx[i], d = y + dy[i];
            if(a >= 0 && a < l && b >= 0 && b < r && d >= 0 && d < c && g[a][b][d] != '#' && dist[a][b][d] == -1){
                q.push({a, b, d});
                dist[a][b][d] = dist[z][x][y] + 1;
                
                if(g[a][b][d] == 'E') return dist[a][b][d];
            }
        }
    }
    return -1;
}

int main(){
    while(cin >> l >> r >> c, l){
        for(int i = 0; i < l; i++)
            for(int j = 0; j < r; j++)
                cin >> g[i][j];
                
        Node start, end;
        for(int i = 0; i < l; i++)
            for(int j = 0; j < r; j++)
                for(int z = 0; z < c; z++)
                    if(g[i][j][z] == 'S') start = {i, j, z};
                    else if(g[i][j][z] == 'E') end = {i, j, z};
        int res = bfs(start, end);
        if(res == -1) cout << "Trapped!" << endl;
        else cout << "Escaped in " << res << " minute(s)." << endl;
    }
    
    return 0;
}

// 大佬的代码
#include<iostream>
#include<cstring>
using namespace std;

const int N = 110;
struct Point{
    int x, y, z;
};

int L, R, C;
char g[N][N][N];
Point q[N * N * N];
int dist[N][N][N];

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, -1, 1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

int bfs(Point start, Point end){
    int hh = 0, tt = 0;
    q[0] = start;
    memset(dist, -1, sizeof dist);
    dist[start.x][start.y][start.z] = 0;
    
    while(hh <= tt){
        auto t = q[hh++];
        
        for(int i = 0; i < 6; i++){
            int x = t.x + dx[i], y = t.y + dy[i], z = t.z + dz[i];
            if(x < 0 || x >= L || y < 0 || y >= R || z < 0 || z >= C) continue; // 出界
            if(g[x][y][z] == '#') continue; // 障碍物
            if(dist[x][y][z] != -1) continue; // 之前走到过
            
            dist[x][y][z] = dist[t.x][t.y][t.z] + 1;
            if(x == end.x && y == end.y && z == end.z) return dist[x][y][z];
            
            q[++tt] = {x, y, z};
        }
    }
    return -1;
}

int main(){
    while(scanf("%d%d%d", &L, &R, &C), L || R || C){
        Point start, end;
        for(int i = 0; i < L; i++)
            for(int j = 0; j < R; j++){
                scanf("%s", g[i][j]);
                for(int k = 0; k < C; k++){
                    char c = g[i][j][k];
                    if(c == 'S') start = {i, j, k};
                    else if(c == 'E') end = {i, j, k};
                }
            }
            
        int distance = bfs(start, end);
        if(distance == -1) puts("Trapped!");
        else printf("Escaped in %d minute(s).\n", distance);
    }
    
    return 0;
}