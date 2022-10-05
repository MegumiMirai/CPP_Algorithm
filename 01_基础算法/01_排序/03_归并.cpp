// 给定你一个长度为 n 的整数数列。

// 请你使用归并排序对这个数列按照从小到大进行排序。

// 并将排好序的数列按顺序输出。

// 输入格式
// 输入共两行，第一行包含整数 n。

// 第二行包含 n 个整数（所有整数均在 1∼109 范围内），表示整个数列。

// 输出格式
// 输出共一行，包含 n 个整数，表示排好序的数列。

// 数据范围
// 1≤n≤100000
// 输入样例：
// 5
// 3 1 2 4 5
// 输出样例：
// 1 2 3 4 5

#include<iostream>
using namespace std;

const int N = 1e6 + 10;

void mergeSort(int q[], int temp[], int l, int r){
    if(l >= r){
        return;
    }
    
    int mid = l + r >> 1;
    int i = l, j = mid + 1, k = 0;
    
    
    mergeSort(q, temp, l, mid);
    mergeSort(q, temp, mid + 1, r);
    
    while(i <= mid && j <= r){
        if(q[i] <= q[j]){
            temp[k++] = q[i++];
        }else{
            temp[k++] = q[j++];
        }
    }
    while(i <= mid){
        temp[k++] = q[i++];
    }
    while(j <= r){
        temp[k++] = q[j++];
    }
    
    for(i = l, j = 0; i <= r; i++, j++){
        q[i] = temp[j];
    }
}

int main(){
    
    int n, q[N], temp[N];
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        scanf("%d", &q[i]);
    }
    
    mergeSort(q, temp, 0, n - 1);
    
    for(int i = 0; i < n; i++){
        printf("%d ", q[i]);
    }
    
    return 0;
}