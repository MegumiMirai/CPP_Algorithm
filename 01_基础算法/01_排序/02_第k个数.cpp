// 给定一个长度为 n 的整数数列，以及一个整数 k，请用快速选择算法求出数列从小到大排序后的第 k 个数。

// 输入格式
// 第一行包含两个整数 n 和 k。

// 第二行包含 n 个整数（所有整数均在 1∼109 范围内），表示整数数列。

// 输出格式
// 输出一个整数，表示数列的第 k 小数。

// 数据范围
// 1≤n≤100000,
// 1≤k≤n
// 输入样例：
// 5 3
// 2 4 1 5 3
// 输出样例：
// 3

#include<iostream>
using namespace std;

int quick_search(int arr[], int l, int r, int k){
    if(l == r) return arr[l];
    
    int x = arr[l + r >> 1];
    int i = l - 1, j =  r + 1;
    while(i < j){
        do i++; while(arr[i] < x);
        do j--; while(arr[j] > x);
        if(i < j) swap(arr[i], arr[j]);
    }
    
    int sl = j - l + 1;
    if(sl >= k)
        return quick_search(arr, l, j, k);
    return quick_search(arr, j + 1, r, k - sl);
    
}

int main(){
    const int N = 1e6 + 10;
    int arr[N];
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> arr[i];
    cout << quick_search(arr, 0, n - 1, k);
    return 0;
}