/*
 * 【 题目描述】小 Q 的公司最近接到 m 个任务, 第 i 个任务需要 xi 的时间去完成, 难度等级为 yi。
小 Q 拥有 n 台机器, 每台机器最长工作时间 zi, 机器等级 wi。
对于一个任务,它只能交由一台机器来完成, 如果安排给它的机器的最长工作时间小于任务需要的时间,
则不能完成,如果完成这个任务将获得 200 * xi + 3 * yi 收益。
对于一台机器,它一天只能完成一个任务, 如果它的机器等级小于安排给它的任务难度等级, 则不能完成。
小 Q 想在今天尽可能的去完成任务, 即完成的任务数量最大。如果有多种安排方案,小 Q 还想找到收益最大
的那个方案。小 Q 需要你来帮助他计算一下。
输入描述 ：
输入包括 N + M + 1 行,
输入的第一行为两个正整数 n 和 m(1 <= n, m <= 100000), 表示机器的数量和任务的数量。
接下来 n 行,每行两个整数 zi 和 wi(0 < zi < 1000, 0 <= wi <= 100), 表示每台机器的最大工作时间和
机器等级。
接下来的 m 行,每行两个整数 xi 和 yi(0 < xi < 1000, 0 <= yi<= 100), 表示每个任务需要的完成时间和
任务的难度等级。
输出描述 ：
输出两个整数, 分别表示最大能完成的任务数量和获取的收益。
输入示例 ：
1 2
100 3
100 2
100 1
输出示例 ：
1 20006
 */
#include <bits/stdc++.h>
//#include <iostream>
//#include <vector>
//#include <algorithm>
using namespace std;
struct node_t{
    int time;
    int lv;
};
bool mac_cmp(const node_t& n1,const node_t& n2){
    if(n1.time==n2.time)return n1.lv<n2.lv;
    return n1.time<n2.time;
}
bool task_cmp(const node_t& n1,const node_t& n2){
    if(n1.time==n2.time)return n1.lv>n2.lv;
    return n1.time>n2.time;
}
int main(){
    int m,n;
    cin>>n>>m;
    vector<node_t> mac(n),task(m);
    for(int i=0;i<n;++i)
        cin>>mac[i].time>>mac[i].lv;
    for(int i=0;i<m;++i)
        cin>>task[i].time>>task[i].lv;
    //greedy strategy, sort task according to time and difficulty
    //find the machine that satisfies the time requirement with the minimum level to do the job
    sort(mac.begin(),mac.end(),mac_cmp);
    sort(task.begin(),task.end(),task_cmp);
    int num=0,res=0;
    vector<int> occupy(n,-1);
    for(int j=0;j<m;++j){
        int minlv=999999,minindex=-1;
        for(int i=0;i<n;++i){
            //past machines don't meet time requirment
            if(mac[i].time<task[j].time)continue;
            //find the machine with minimum level
            if(occupy[i]==-1 && mac[i].lv>=task[j].lv && mac[i].lv<minlv){
                minlv=mac[i].lv;
                minindex=i;
            }
        }
        if(minindex!=-1){
            occupy[minindex] = j;
            ++num;
            res+=200*task[j].time+3*task[j].lv;
        }
    }
    cout<<num<<" "<<res<<endl;
    return 0;
}
/*
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int maxn = 1e5 + 10;
struct node {
    int x, y;
}e[maxn], f[maxn];
int cnt[105];
int cmp(node a, node b) {
    if(a.x == b.x)return a.y > b.y;
    return a.x > b.x;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%d%d", &e[i].x, &e[i].y);
    for(int i = 0; i < m; i++) scanf("%d%d", &f[i].x, &f[i].y);
    sort(e, e + n, cmp);
    sort(f, f + m, cmp);
    int num = 0;
    LL ans = 0;
    memset(cnt, 0, sizeof(cnt));
    int i, j, k;
    for(i = 0, j = 0; i < m; i++) {
        while(j < n && e[j].x >= f[i].x) {
            cnt[e[j].y]++;
            j++;
        }
        for(k = f[i].y; k <= 100; k++) {
            if(cnt[k]) {
                num++;
                cnt[k]--;
                ans = ans + 200 * f[i].x + 3 * f[i].y;
                break;
            }
        }
    }
    printf("%d %lld\n", num, ans);
    return 0;
}
 */