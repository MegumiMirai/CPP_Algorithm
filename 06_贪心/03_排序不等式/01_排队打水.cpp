// 有 n 个人排队到 1 个水龙头处打水，第 i 个人装满水桶所需的时间是 ti，请问如何安排他们的打水顺序才能使所有人的等待时间之和最小？

// 输入格式
// 第一行包含整数 n。

// 第二行包含 n 个整数，其中第 i 个整数表示第 i 个人装满水桶所花费的时间 ti。

// 输出格式
// 输出一个整数，表示最小的等待时间之和。

// 数据范围
// 1≤n≤105,
// 1≤ti≤104
// 输入样例：
// 7
// 3 6 1 4 2 5 7
// 输出样例：
// 56

/*
比如说给定一组数，3 6 1 4 2 5 7，按照从前到后打水，所需要的时间为：3*6 + 6*5 + 1*4 + 4*3 + 2*2 + 5*1 + 7*0
可以推出来总时间 = t1 * (n - 1) + t2 * (n - 2) + ... + t(n-1) * 1 + tn * 0
如果要时间最少，只需要将这一组数从小到大排序，再使用公式即可
证明：
  使用反证法，比如果不是按照升序，ti > t(i + 1)
  前：... + ti * (n - i) + t(i + 1) * (n - i - 1) + ...
  后：... + t(i + 1) * (n - i) + ti * (n - i - 1) + ...
  前 - 后 = ti - t(i - 1) > 0，也就表示所需要的时间更多，出现矛盾，所以结论是正确的
*/
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 1e5 + 10;
int a[N];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    LL res = 0;
    for(int i = 0; i < n; i++) res += a[i] * (n - i - 1);
    cout << res << endl;
    return 0;
}