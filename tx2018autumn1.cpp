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
#include <iostream>
#include <vector>
using  namespace std;
int factorial(int n){
    if(n==0)return 1;
    int f=1;
    for(int i=1;i<=n;++i)f*=i;
    return f;
}
int combination(int M,int N){
    return factorial(M)/(factorial(N)*factorial(M-N));
}
int main(){
    int K,A,B,X,Y;
    cin>>K>>A>>B>>X>>Y;
    vector<pair<int,int>> possibleAB;
    for(int i=0;i<=K/A;++i){
        int t=(K-i*A)/B;
        if(i*A+B*t==K)
            possibleAB.push_back(make_pair(i,t));
    }
    int count=0;
    for(auto p:possibleAB)
        if(A>=p.first && B>=p.second)
            count=(count+combination(A,p.first)*combination(B,p.second))%1000000007;
    cout<<count<<endl;
}
