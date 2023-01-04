// 设有 N×N 的方格图，我们在其中的某些方格中填入正整数，而其它的方格中则放入数字0。如下图所示：

// 2.gif

// 某人从图中的左上角 A 出发，可以向下行走，也可以向右行走，直到到达右下角的 B 点。

// 在走过的路上，他可以取走方格中的数（取走后的方格中将变为数字0）。

// 此人从 A 点到 B 点共走了两次，试找出两条这样的路径，使得取得的数字和为最大。

// 输入格式
// 第一行为一个整数N，表示 N×N 的方格图。

// 接下来的每行有三个整数，第一个为行号数，第二个为列号数，第三个为在该行、该列上所放的数。

// 行和列编号从 1 开始。

// 一行“0 0 0”表示结束。

// 输出格式
// 输出一个整数，表示两条路径上取得的最大的和。

// 数据范围
// N≤10
// 输入样例：
// 8
// 2 3 13
// 2 6 6
// 3 5 7
// 4 4 14
// 5 2 21
// 5 6 4
// 6 3 15
// 7 2 14
// 0 0 0
// 输出样例：
// 67

/*
从摘花生扩展过来，摘花生是只走一次，这道题是走两次
所以f[i1, j1, i2, j1]表示所有从(1, 1)(1, 1)分别走到(i1, j1)(i2, j2)的路径的最大值
只有在i1 + j1 == i2 + j2时，两条路径的格子才可能重合
f[k, i1, j1]表示所有从(1, 1)(1, 1)分别走到(i1, k - i1)(i2, k - i2)的路径的最大值
k表示两条路线当前走到的格子的横纵坐标之和，即k = i1 + j1 = i2 + j2
状态计算：Max
  第一条：下 第二条：下 f[k - 1][i1 - 1][i2 - 1]
  第二条：下 第二条：右 f[k - 1][i1 - 1][i2]
  第三条：右 第二条：下 f[k - 1][i1][i2 - 1]
  第四条：右 第二条：右 f[k - 1][i1][i2]
  当两个点重合：w[i1][j1]，不重合：w[i1][j1] + w[i2][j2]
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 11;
int w[N][N];
int f[21][N][N];

int main(){
    int n;
    cin >> n;
    int a, b, c;
    while(cin >> a >> b >> c, a || b || c) w[a][b] = c;
    
    for(int k = 2; k <= n + n; k++) // 从(1, 1)出发，所以i1 + j1 = i2 + j2 = 1 + 1 = 2
        for(int i1 = 1; i1 <= n; i1++)
            for(int i2 = 1; i2 <= n; i2++){
                int j1 = k - i1, j2 = k - i2; 
                int t = w[i1][j1]; 
                if(i1 != i2) t += w[i2][j2]; // 如果不重合，两个相加 
                
                if(j1 >= 1 && j1 <= n && j2 >= 1 && j2 <= n){ // 如果所有点都在范围内，就取最大值
                    f[k][i1][i2] = max(max(f[k - 1][i1 - 1][i2 - 1], f[k - 1][i1 - 1][i2]), max(f[k - 1][i1][i2 - 1], f[k - 1][i1][i2])) + t;
                }
            }
            
    cout << f[n + n][n][n] << endl; // 表示最终横纵坐标和为n + n，横坐标 = 纵坐标 = n时两条路径之和
    
    return 0;
}