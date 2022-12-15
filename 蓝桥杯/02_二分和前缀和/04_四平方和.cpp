// 四平方和定理，又称为拉格朗日定理：

// 每个正整数都可以表示为至多 4 个正整数的平方和。

// 如果把 0 包括进去，就正好可以表示为 4 个数的平方和。

// 比如：

// 5=02+02+12+22
// 7=12+12+12+22
// 对于一个给定的正整数，可能存在多种平方和的表示法。

// 要求你对 4 个数排序：

// 0≤a≤b≤c≤d
// 并对所有的可能表示法按 a,b,c,d 为联合主键升序排列，最后输出第一个表示法。

// 输入格式
// 输入一个正整数 N。

// 输出格式
// 输出4个非负整数，按从小到大排序，中间用空格分开。

// 数据范围
// 0<N<5∗106
// 输入样例：
// 5
// 输出样例：
// 0 0 1 2

// 方法一：二分
// 从下到大枚举c和d，将他们保存起来，然后从小到大枚举a和b，查看保存起来的c和d中是否存在n-a*a-b*b，如果存在，则第一个就是字典序最小的，输出即可
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

const int N = 2500010; // sqrt(n) <= n/2，所以数组只需要开一半即可
struct Sum{ // Sum结构体是用来保存 c*c+d*d，c，d
    int s, c, d;
    bool operator<(const Sum &t) const{ // 重写<用于排序
        if(s != t.s) return s < t.s;
        if(c != t.c) return c < t.c;
        return d < t.d;
    }
}sum[N];
int n, m;

int main(){
    cin >> n;
    for(int c = 0; c * c <= n; c++)
        for(int d = c; c * c + d * d <= n; d++)
            sum[m++] = {c * c + d * d, c, d}; // 枚举c和d，保存起来
    sort(sum, sum + m); 
    for(int a = 0; a * a <= n; a++)
        for(int b = a; a * a + b * b <= n; b++){ // 从小到大枚举a和b
            int t = n - a * a - b * b; // 获取剩余的平方和
            int l = 0, r = m - 1;
            while(l < r){ // 二分这个结构体数组
                int mid = l + r >> 1;
                if(sum[mid].s >= t) r = mid;
                else l = mid + 1;
            }
            if(sum[l].s == t){ // 如果存在
                printf("%d %d %d %d\n", a, b, sum[l].c, sum[l].d); // 则它就是字典序最小的，输出即可
                return 0;
            }
        }
    return 0;
}

// 方法二：哈希表
// 会超时，思路和二分一样，只是用哈希表保存更方便，他会自动排序，并且哈希表的Count函数可以判断是否存在，更方便
#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;

#define x first
#define y second

typedef pair<int, int> PII;
const int N = 2500010;
int n, m;
unordered_map<int, PII> S;

int main(){
    cin >> n;
    for(int c = 0; c * c <= n; c++)
        for(int d = c; c * c + d * d <= n; d++){
            int t = c * c + d * d;
            if(S.count(t) == 0) S[t] = {c, d};
        }
    for(int a = 0; a * a <= n; a++)
        for(int b = a; a * a + b * b <= n; b++){
            int t = n - a * a - b * b;
            if(S.count(t)){
                printf("%d %d %d %d\n", a, b, S[t].x, S[t].y);
                return 0;
            }
        }
    return 0;
}