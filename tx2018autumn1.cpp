/*
 * 小Q有X首长度为A的不同的歌和Y首长度为B的不同的歌，
 * 现在小Q想用这些歌组成一个总长度正好为K的歌单，
 * 每首歌最多只能在歌单中出现一次，在不考虑歌单内歌曲的先后顺序的情况下，
 * 请问有多少种组成歌单的方法。
 * 每个输入包含一个测试用例。
每个测试用例的第一行包含一个整数，表示歌单的总长度K(1<=K<=1000)。
接下来的一行包含四个正整数，分别表示歌的第一种长度A(A<=10)和
 数量X(X<=100)以及歌的第二种长度B(B<=10)和数量Y(Y<=100)。保证A不等于B。
 输出一个整数,表示组成歌单的方法取模。因为答案可能会很大,输出对1000000007取模的结果。

输入例子1:
5
2 3 3 3
 输出例子1:
9
 */
#include <bits/stdc++.h>
using  namespace std;
const int mod = 1000000007;
long long exp_mod(long long a, long long b, long long p)
{
    long long res = 1;
    while(b != 0)
    {
        if(b&1) res = (res * a) % p;
        a = (a*a) % p;
        b >>= 1;
    }
    return res;
}

long long Comb(long long a, long long b, long long p)
{
    if(a < b)   return 0;
    if(a == b)  return 1;
    if(b > a - b)   b = a - b;

    long long ans = 1, ca = 1, cb = 1;
    for(long long i = 0; i < b; ++i)
    {
        ca = (ca * (a - i))%p;
        cb = (cb * (b - i))%p;
    }
    ans = (ca*exp_mod(cb, p - 2, p)) % p;
    return ans;
}

long long Lucas(int n, int m, int p)
{
    long long ans = 1;

    while(n&&m&&ans)
    {
        ans = (ans*Comb(n%p, m%p, p)) % p;
        n /= p;
        m /= p;
    }
    return ans;
}
int main(){
    int K,A,B,X,Y;
    cin>>K>>A>>X>>B>>Y;
    vector<pair<int,int>> possibleAB;
    if(A!=0) {
        if(B!=0)
            for (int i = 0; i <= K / A; ++i) {
                int t=(K - i * A) / B;
                if (i * A + B * t == K)
                    possibleAB.push_back(make_pair(i, t));
            }
        else
        if(K%A==0)
            possibleAB.push_back(make_pair(K/A,0));
    }
    else
        if(K%B==0)
            possibleAB.push_back(make_pair(0,K/B));
    int count=0;
    for(auto p:possibleAB)
        if(X>=p.first && Y>=p.second)
            count=(count+Lucas(X,p.first,mod)*Lucas(Y,p.second,mod))%mod;
    cout<<count;
    return 0;
}
