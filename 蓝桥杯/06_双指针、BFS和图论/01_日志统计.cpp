// 小明维护着一个程序员论坛。现在他收集了一份”点赞”日志，日志共有 N 行。

// 其中每一行的格式是：

// ts id  
// 表示在 ts 时刻编号 id 的帖子收到一个”赞”。

// 现在小明想统计有哪些帖子曾经是”热帖”。

// 如果一个帖子曾在任意一个长度为 D 的时间段内收到不少于 K 个赞，小明就认为这个帖子曾是”热帖”。

// 具体来说，如果存在某个时刻 T 满足该帖在 [T,T+D) 这段时间内(注意是左闭右开区间)收到不少于 K 个赞，该帖就曾是”热帖”。

// 给定日志，请你帮助小明统计出所有曾是”热帖”的帖子编号。

// 输入格式
// 第一行包含三个整数 N,D,K。

// 以下 N 行每行一条日志，包含两个整数 ts 和 id。

// 输出格式
// 按从小到大的顺序输出热帖 id。

// 每个 id 占一行。

// 数据范围
// 1≤K≤N≤105,
// 0≤ts,id≤105,
// 1≤D≤10000
// 输入样例：
// 7 10 2
// 0 1
// 0 10
// 10 10
// 10 1
// 9 1
// 100 3
// 100 3
// 输出样例：
// 1
// 3


/*
for(时间段){
  计算该时间段每个id的点赞数
  如果点赞数 >= k
  st[id] = true
}
如果里面也使用一个循环来枚举每一个id，时间复杂度是O(n^2)或者O(nm)，是十次方级别，可能会TLE，所以需要优化中间的代码
可以发现
————————————————————
  ————————————————————
如果每次时间段内的都要计算一遍，有很多冗余，从这里下手
每次减去前面一段时间的id，后面一段时间的id再加上，时间复杂度就是O(n)
*/
#include<iostream>
#include<algorithm>
using namespace std;

#define x first
#define y second

const int N = 1e5 + 10;
typedef pair<int, int> PII;
PII logs[N]; // 保存记录
int cnt[N]; // 记录一段时间内每个id的点赞数
bool st[N]; // 记录某一个帖子在过去是否是热帖
int n, d, k;

int main(){
    cin >> n >> d >> k;
    for(int i = 0; i < n; i++){
        cin >> logs[i].x >> logs[i].y;
    }
    
    sort(logs, logs + n); // 让记录按照时间顺序从小到大排序
    for(int i = 0, j = 0; i < n; i++){ // 枚举一个时间段，i在后，j在前
        int id = logs[i].y; // 获取i这个坐标的帖子的id
        cnt[id]++; // 让这个帖子点赞数+1
        
        while(logs[i].x - logs[j].x >= d){ // 然后查看i和j下标位置时间跨度是否大等于d，如果大等于，j需要往后移
            cnt[logs[j].y]--; // 首先把j下标位置的帖子点赞数减1
            j++; // 让后j向后移
        }
        
        if(cnt[id] >= k) st[id] = true; // 之后在判断id的帖子点赞数是否大于等于k，只判断这一个是因为每次只算一个帖子，只要id这个帖子点赞数加1
    }
    
    for(int i = 0; i <= 100000; i++) // 最后查看每个id的st是否为true，题目给出的id范围是[0, 1e5]，所以相应的要枚举这里面每一个数
        if(st[i])  
            cout << i << endl;
    
    return 0;
}