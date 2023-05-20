#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include <bits/stdc++.h>
using namespace std;

#ifdef WAIMAI
#define debug(HEHE...) cout << "[" << #HEHE << "] : ", dout(HEHE)
void dout() {cout << '\n';}
template<typename T, typename...U>
void dout(T t, U...u) {cout << t << (sizeof...(u) ? ", " : ""), dout(u...);}
#else
#define debug(...) 7122
#endif

#define ll long long
#define Waimai ios::sync_with_stdio(false), cin.tie(0)
#define FOR(x,a,b) for (int x = a, I = b; x <= I; x++)
#define pb emplace_back
#define F first
#define S second

const string GEN = "gen";
const string BRU = "brute";
const string PRO = "project";

int main() {
    while (1) {
        system((GEN + ".exe > input.txt").c_str());
        system((BRU + ".exe < input.txt > " + BRU + ".txt").c_str());
        system((PRO + ".exe < input.txt > " + PRO + ".txt").c_str());
        if (system(("fc " + PRO + ".txt " + BRU + ".txt").c_str())) {
            break;
        }
    }
}
