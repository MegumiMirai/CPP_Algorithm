// 给定 n 组询问，每组询问给定三个整数 a,b,p，其中 p 是质数，请你输出 Cbamodp 的值。

// 输入格式
// 第一行包含整数 n。

// 接下来 n 行，每行包含一组 a,b,p。

// 输出格式
// 共 n 行，每行输出一个询问的解。

// 数据范围
// 1≤n≤20,
// 1≤b≤a≤1018,
// 1≤p≤105,

// 输入样例：
// 3
// 5 3 7
// 3 1 5
// 6 4 13
// 输出样例：
// 3
// 3
// 2

// 卢卡斯定理 C(a, b) = C(a % p, b % p) * lucas(a / p, b / p)，如果a和b都小于p，就按照定义来做
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;

int p;

int qmi(int a, int k){
    int res = 1;
    while(k){
        if(k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}


int C(int a, int b){
    int res = 1;
    for(int i = 1, j = a; i <= b; i++, j--){
        res = (LL)res * j % p;
        res = (LL)res * qmi(i, p - 2) % p;
    }
    return res;
}

int lucas(LL a, LL b){
    if(a < p && b < p) return C(a, b);
    return (LL)C(a % p, b % p) * lucas(a / p, b / p) % p;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        LL a, b;
        cin >> a >> b >> p;
        cout << lucas(a, b) << endl;
    }
    return 0;
}