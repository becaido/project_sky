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

mt19937 seed(time(NULL));
template<typename T = int>
inline T rnd(T l, T r) {
    return uniform_int_distribution<T>(l, r)(seed);
}
template<typename T = double>
inline T srnd(T l, T r) {
    return uniform_real_distribution<T>(l, r)(seed);
}

void solve() {

}

int main() {
    Waimai;
    solve();
}
