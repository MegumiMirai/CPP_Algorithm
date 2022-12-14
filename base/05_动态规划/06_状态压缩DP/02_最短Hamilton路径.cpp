// 给定一张 n 个点的带权无向图，点从 0∼n−1 标号，求起点 0 到终点 n−1 的最短 Hamilton 路径。

// Hamilton 路径的定义是从 0 到 n−1 不重不漏地经过每个点恰好一次。

// 输入格式
// 第一行输入整数 n。

// 接下来 n 行每行 n 个整数，其中第 i 行第 j 个整数表示点 i 到 j 的距离（记为 a[i,j]）。

// 对于任意的 x,y,z，数据保证 a[x,x]=0，a[x,y]=a[y,x] 并且 a[x,y]+a[y,z]≥a[x,z]。

// 输出格式
// 输出一个整数，表示最短 Hamilton 路径的长度。

// 数据范围
// 1≤n≤20
// 0≤a[i,j]≤107
// 输入样例：
// 5
// 0 2 4 5 1
// 2 0 6 5 3
// 4 6 0 8 3
// 5 5 8 0 5
// 1 3 3 5 0
// 输出样例：
// 18

/*
如果暴力求解，那么每一个点都要经过，有n!种方法，然后要求路径，所以时间复杂度是O(n! * n)，规定n是小于等于20的，20! * 20是很恐怖的，不用说肯定过不去
那么就要想办法优化，就用到了状态压缩
状态表示f[i, j]：
  集合：所有从0走到j，走过的点都包含在i中的所有路径，i是一个二进制数，表示某个点是否经过，如 10110表示经过第1、2、4这三个点但是没经过0和3这两个点
  属性：Min
状态计算：用什么办法可以把所有的状态一个不漏的都表示出来呢？这么想，如果从0走到j，那么枚举在到达j之前经过的所有点，然后把它们相加即可
         比如说，一共有5个点，0,1,2,3,4，那么从0走到4，在走到4之前有到达0、1、2、3、4这五种
         所以 f[i][j] = f[i - {j}][k] + w[k][j]，k表示倒数第二个点，i-{j}表示i这个路径中除去j，也就是不经过j点
*/
#include<iostream>
#include<cstring>
using namespace std;

const int N = 20, M = 1 << N;

int n;
int w[N][N]; // 存储无向图
int f[M][N]; // 一维表示所有的方案，二维表示走到的终点

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> w[i][j]; // 从控制台读取数据
    
    memset(f, 0x3f, sizeof f); // 因为是求最小值，所以我们先把所有数都设置成无穷大
    f[1][0] = 0; // 这个意思是，从0走到0，那么它只经过0这个点，0这个点在二进制中用1表示，所以f[1][0] = 0
    for(int i = 0; i < 1 << n; i++) // 枚举所有方案
        for(int j = 0; j < n; j++) // 枚举所有终点
            if(i >> j & 1) // 只有终点j在i这个方案中有经过才进行后续操作，不然连j都没有经过，后面操作也就没有意义了
                for(int k = 0; k < n; k++) // 这个是枚举所有在到达j之前先经过的点
                    if((i - (1 << j)) >> k & 1) // 从0到k需要保证不经过j点，然后只有当经过k的时候，才可以判断
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]); // 表示从0到k的距离，路径保存在i中，然后再加上k点和j点之间的权值
    cout << f[(1 << n) - 1][n - 1] << endl; // 最后这个输出的意思是从0到达n-1这个点，并且他的方案是 111111111.... ，表示所有点都经过
    
    return 0;
}

// 简化版
#include<iostream>
#include<cmath>
using namespace std;

int dgt(int x){ // 计算整数n有多少位
    int res = 0;
    while(x) res++, x /= 10;
    return res;
}

int count(int n, int x){ // 计算从1到n的整数中数字i出现多少次 
    int res = 0, d = dgt(n);
    for(int i = 1; i <= d; i++){ // 从右到左第i位上数字x出现多少次
        int p = pow(10, i - 1), r = n % p, l = n / p / 10, dj = n / p % 10; // l和r是第j位左边和右边的整数 (视频中的abc和efg); dj是第j位的数字
        if (x) res += l * p;  // 计算第j位左边的整数小于l (视频中xxx = 000 ~ abc - 1)的情况
        if (!x && l) res += (l - 1) * p;  // 如果x = 0, 左边高位不能全为0(视频中xxx = 001 ~ abc - 1)
        // 计算第i位左边的整数等于l (视频中xxx = abc)的情况
        if ( (dj > x) && (x || l) ) res += p;
        if ( (dj == x) && (x || l) ) res += r + 1;
    }
    return res;
}

int main(){
    int a, b;
    while(cin >> a >> b, a || b){
        if(a > b) swap(a, b);
        for(int i = 0; i < 10; i++)
            cout << count(b, i) - count(a - 1, i) << " ";
        cout << endl;
    }
    
    return 0;
}