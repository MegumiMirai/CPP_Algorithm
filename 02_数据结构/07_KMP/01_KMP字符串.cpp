// 给定一个字符串 S，以及一个模式串 P，所有字符串中只包含大小写英文字母以及阿拉伯数字。

// 模式串 P 在字符串 S 中多次作为子串出现。

// 求出模式串 P 在字符串 S 中所有出现的位置的起始下标。

// 输入格式
// 第一行输入整数 N，表示字符串 P 的长度。

// 第二行输入字符串 P。

// 第三行输入整数 M，表示字符串 S 的长度。

// 第四行输入字符串 S。

// 输出格式
// 共一行，输出所有出现位置的起始下标（下标从 0 开始计数），整数之间用空格隔开。

// 数据范围
// 1≤N≤105
// 1≤M≤106
// 输入样例：
// 3
// aba
// 5
// ababa
// 输出样例：
// 0 2

#include<iostream>
using namespace std;

const int N = 100010, M = 1000010;
char p[N], s[M]; // p是短的字符串，s是长的字符串
int ne[N]; // 保存前缀和后缀最长的相同字符串长度

int main(){
  int n, m;
  cin >> n >> p + 1 >> m >> s + 1; // 两个数组下标都从1开始
  // 更新ne数组
  for(int i = 2, j = 0; i <= n; i++){ // i从2开始，是因为只有一个字符的时候ne[1]=0，这是个特殊情况
    while(j && p[j + 1] != p[i]) j = ne[j]; // 如果p[j + 1]与p[i]不匹配，就找前缀
    if(p[j + 1] == p[i]) j++; // 如果p[j + 1] == p[i]，就往后一位，然后继续匹配
    ne[i] = j; // 保存当前的前缀和后缀最长的相同字符串长度
  }
  // kmp匹配
  for(int i = 1, j = 0; i <= m; i++){
    while(j && p[j + 1] != s[i]) j = ne[j]; // 如果p[j + 1]与s[i]不匹配，就找前缀
    if(p[j + 1] == s[i]) j++; // 如果p[j + 1] == s[i]，就往后一位，然后继续匹配
    if(j == n){ // 此时说明子串已经匹配到最后一个字符了，输出
      printf("%d ", i - n);
      j = ne[j]; // 此时直接移到它的前缀
    }
  }
  return 0;
}