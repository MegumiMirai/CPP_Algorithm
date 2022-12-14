// 给定 n 堆石子，两位玩家轮流操作，每次操作可以从任意一堆石子中拿走任意数量的石子（可以拿完，但不能不拿），最后无法进行操作的人视为失败。

// 问如果两人都采用最优策略，先手是否必胜。

// 输入格式
// 第一行包含整数 n。

// 第二行包含 n 个数字，其中第 i 个数字表示第 i 堆石子的数量。

// 输出格式
// 如果先手方必胜，则输出 Yes。

// 否则，输出 No。

// 数据范围
// 1≤n≤105,
// 1≤每堆石子数≤109
// 输入样例：
// 2
// 2 3
// 输出样例：
// Yes

/*
先手必胜状态：进行一步操作后可以走到某一个必败状态
先手必败状态：走不到一个必败状态，也就是不管自己怎么走都不会让别人必败
现在有两种情况：
  情况一：如果 a1 ^ a2 ^ ... ^ an = x != 0，那么x的二进制表示中最高一位在第k位，那么a1-an中必然存在一个数ai，ai的第k位是1，此时 ai^x < ai是恒成立的
          所以，假设从ai石头中取出 ai - (ai - x) 个石头，此时还剩下 ai - (ai - (ai - x)) = ai ^ x 个石头
          此时原来的式子就变成了 a1 ^ a2 ^ ... ^ ai' ^ a(i+1) ^ ... ^ an = x ^ x = 0，就是说从ai中任意一堆石头中取出一些石头后可以让式子变成0
          使得对手变成必败状态
  情况二：如果 (1):a1 ^ a2 ^ ... ^ an == 0，假设从ai这一堆石头中取出一些石头后变成了ai'个石头，此时 a1 ^ a2 ^ ... ^ ai' ^ ... ^ an != 0 一定成立
          使用反证法，假设它还是等于0的，即 (2):a1 ^ a2 ^ ... ^ ai' ^ ... ^ an == 0，那么把（1）和（2）异或起来，结果是 ai ^ ai' == 0，
          也就说明 ai = ai'，但是它是一定会取出石头的，发生了矛盾，所以 a1 ^ a2 ^ ... ^ ai' ^ ... ^ an != 0 一定成立
  因为 0 ^ 0 ^ ... ^ 0 = 0，所以我只要通过某种方式保证轮到我的回合的时候异或起来不为0，而对手回合的时候异或等于0，最终就会使得对手遇上 0 ^ 0 ^ ... ^ 0
  的局面，所以通过这种方式可以保证先手必胜
这道题要确认先手是必胜还是必败，只需要将所有石头个数异或起来，如果不等于0，就是先手必胜，因为先手可以通过拿走一定的石头使得对手必败
而如果异或起来等于0，那么先手拿走任意一堆任意多的石头后，它的异或就不为0了，也就是先手把必胜的机会让给了后手，使得自己变成了必败状态
*/
#include<iostream>
using namespace std;

int main(){
    int n, res = 0;
    cin >> n;
    while(n--){
        int x;
        cin >> x;
        res ^= x;
    }
    if(res) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}