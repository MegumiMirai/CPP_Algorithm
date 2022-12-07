// 把 1∼n 这 n 个整数排成一行后随机打乱顺序，输出所有可能的次序。

// 输入格式
// 一个整数 n。

// 输出格式
// 按照从小到大的顺序输出所有方案，每行 1 个。

// 首先，同一行相邻两个数用一个空格隔开。

// 其次，对于两个不同的行，对应下标的数一一比较，字典序较小的排在前面。

// 数据范围
// 1≤n≤9
// 输入样例：
// 3
// 输出样例：
// 1 2 3
// 1 3 2
// 2 1 3
// 2 3 1
// 3 1 2
// 3 2 1

#include<iostream>
using namespace std;

const int N = 10;
int n;
int num[N]; // 保存一种方案
bool st[N]; // 保存这个数是否已经用过

void dfs(int u){
    if(u > n) { // 边界，如果u>n，就输出当前的方案
        for(int i = 1; i <= n; i++) cout << num[i] << " ";
        cout << endl;
    }
    
    for(int i = 1; i <= n; i++){ // 从头开始枚举每一个数
        if(!st[i]){ // 如果当前数还没使用过
            st[i] = true; // 把它标记为使用了
            num[u] = i; // 并且把它存进这一种方案中
            dfs(u + 1); // 开始向下递归下一个数
            
            st[i] = false; // 还原，重新把它设置成还没有使用
        }
    }
}

int main(){
    cin >> n;
    dfs(1);
    return 0;
}