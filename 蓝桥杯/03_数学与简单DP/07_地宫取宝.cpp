// X 国王有一个地宫宝库，是 n×m 个格子的矩阵，每个格子放一件宝贝，每个宝贝贴着价值标签。

// 地宫的入口在左上角，出口在右下角。

// 小明被带到地宫的入口，国王要求他只能向右或向下行走。

// 走过某个格子时，如果那个格子中的宝贝价值比小明手中任意宝贝价值都大，小明就可以拿起它（当然，也可以不拿）。

// 当小明走到出口时，如果他手中的宝贝恰好是 k 件，则这些宝贝就可以送给小明。

// 请你帮小明算一算，在给定的局面下，他有多少种不同的行动方案能获得这 k 件宝贝。

// 输入格式
// 第一行 3 个整数，n,m,k，含义见题目描述。

// 接下来 n 行，每行有 m 个整数 Ci 用来描述宝库矩阵每个格子的宝贝价值。

// 输出格式
// 输出一个整数，表示正好取 k 个宝贝的行动方案数。

// 该数字可能很大，输出它对 1000000007 取模的结果。

// 数据范围
// 1≤n,m≤50,
// 1≤k≤12,
// 0≤Ci≤12
// 输入样例1：
// 2 2 2
// 1 2
// 2 1
// 输出样例1：
// 2
// 输入样例2：
// 2 3 2
// 1 2 3
// 2 1 5
// 输出样例2：
// 14

/*
动态规划：
  状态表示f[i,j,k,c]
    集合：所有从起点走到(i, j)，且已经取了k件物品，且最后一件物品的价值是c的合法方案的集合
    属性：Count
  状态计算：
    所有最后一步是从上往下的走法：
      （1）不取
      （2）取 f[i - 1, j, k - 1, c']  c' < c
    所有最后一步是从左往右的走法：
      （1）不取
      （2）取 f[i, j - 1, k - 1, c'] c' < c
*/
#include<iostream>
using namespace std;

const int N = 55, MOD = 1000000007;

int n, m, k;
int w[N][N]; // 存储每个物品的价值
int f[N][N][13][14]; // 所有从起点走到(i, j)，且已经取了k件物品，且最后一件物品的价值是c，c最大是14是因为让所有物品的价值都增加1，此时价值为0就表示不选

int main(){
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            cin >> w[i][j];
            w[i][j]++; // 因为价值是从0开始的，但是数组中无法使用-1来表示不取该物品，所以让价值为0的物品变为1，这样的话不选当前价值就为0
        }
    
    f[1][1][1][w[1][1]] = 1; // (1,1)位置选择的方案数
    f[1][1][0][0] = 1; // (1,1)位置不选择的方案数
    
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            if(i == 1 && j == 1) continue; // (1,1)位置已经初始化好了，跳过
            for(int u = 0; u <= k; u++){ // 枚举k件物品
                for(int v = 0; v <= 13; v++){ // 枚举最后一件物品价值
                    int &val = f[i][j][u][v]; 
                    val = (val + f[i - 1][j][u][v]) % MOD; // 从上往下走不选择
                    val = (val + f[i][j - 1][u][v]) % MOD; // 从左往右走不选择
                    if(u > 0 && v == w[i][j]){ // 如果起码选择一件物品，并且选择(i,j)这件物品
                        for(int c = 0; c < v; c++){ // 就枚举上一件物品的价值，这个物品的价值必须小于v
                            val = (val + f[i - 1][j][u - 1][c]) % MOD;
                            val = (val + f[i][j - 1][u - 1][c]) % MOD;
                        }
                    }
                }
            }
        }
    
    int res = 0;
    for(int i = 1; i <= 13; i++) res = (res + f[n][m][k][i]) % MOD; // 将所用从起点走到(n,m)，并且去了k件物品，最后一件物品价值从1-13累加
    cout << res << endl;
    return 0;
}