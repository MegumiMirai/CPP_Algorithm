// 输入一个长度为 n 的整数数列，从小到大输出前 m 小的数。

// 输入格式
// 第一行包含整数 n 和 m。

// 第二行包含 n 个整数，表示整数数列。

// 输出格式
// 共一行，包含 m 个整数，表示整数数列中前 m 小的数。

// 数据范围
// 1≤m≤n≤105，
// 1≤数列中元素≤109
// 输入样例：
// 5 3
// 4 5 1 3 2
// 输出样例：
// 1 2 3

#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int n, m;
int heap[N], sz;

void down(int u){
  int t = u;
  if(u * 2 <= sz && heap[u * 2] < heap[t]) t = u * 2;
  if(u * 2 + 1 <= sz && heap[u * 2 + 1] < heap[t]) t = u * 2 + 1;
  if(t != u){
    swap(heap[t], heap[u]);
    down(t);
  }
}

int main(){
  cin >> n >> m;
  sz = n;
  for(int i = 1; i <= n; i++) cin >> heap[i];
  for(int i = n / 2; i; i--) down(i);
  while(m--){
    cout << heap[1] << " ";
    heap[1] = heap[sz];
    sz--;
    down(1);
  }
  return 0;
}