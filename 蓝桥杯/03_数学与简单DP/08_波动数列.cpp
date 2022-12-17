// 观察这个数列：

// 1 3 0 2 -1 1 -2 …

// 这个数列中后一项总是比前一项增加2或者减少3，且每一项都为整数。

// 栋栋对这种数列很好奇，他想知道长度为 n 和为 s 而且后一项总是比前一项增加 a 或者减少 b 的整数数列可能有多少种呢？

// 输入格式
// 共一行，包含四个整数 n,s,a,b，含义如前面所述。

// 输出格式
// 共一行，包含一个整数，表示满足条件的方案数。

// 由于这个数很大，请输出方案数除以 100000007 的余数。

// 数据范围
// 1≤n≤1000,
// −109≤s≤109,
// 1≤a,b≤106
// 输入样例：
// 4 10 2 3
// 输出样例：
// 2
// 样例解释
// 两个满足条件的数列分别是2 4 1 3和7 4 1 -2。

/*
动态规划：
  状态表示：
    集合：所有只考虑前i项，且当前的总和除以n的余数是j的方案的集合
    属性：Count
  状态计算：
    最后一项是+a的所有方案 f[i - 1, (j - i * a) % mod]
    最后一项是-b的所有方案 f[i - 1, (j + i * b) % mod]

di属于{+a, -b}
x  x+d1  x+d1+d2  x+d1+d2+d3   + ... + x+d1+d2+...+d(n-1)
nx + (n-1)d1 + (n-2)d2 + ... + d(n-1) = S
x = (S - ((n-1)d1 + (n-2)d2 + ... + d(n-1))) / n
即(n-1)d1 + (n-2)d2 + ... + d(n-1) 与 S 模n的余数相同
那么答案就是f[n-1][s%n] n-1是因为下标从0开始，所以n-1就相当于是考虑前n项，模数是s%n的方案数
初始条件是 f[0][0] = 1
*/
#include<iostream>
using namespace std;

const int N = 1010, MOD = 100000007;
int f[N][N];

int get_mod(int a, int b){ // 获取正余数
    return (a % b + b) % b;
}

int main(){
    int n, s, a, b;
    cin >> n >> s >> a >> b;
    
    f[0][0] = 1;
    for(int i = 1; i < n; i++)
        for(int j = 0; j < n; j++)
            f[i][j] = (f[i - 1][get_mod(j - a * i, n)] + f[i - 1][get_mod(j + b * i, n)]) % MOD;
    
    cout << f[n - 1][get_mod(s, n)] << endl;
    
    return 0;
}