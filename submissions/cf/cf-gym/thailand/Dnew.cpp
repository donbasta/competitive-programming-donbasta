#include<bits/stdc++.h>
using namespace std;
 
/** START OF DESPERATE OPTIMIZATION **/
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
template<typename T> void in(T & x) {
    x = 0;
    register T c = getchar();
    while (((c < 48) || (c > 57)) && (c != '-')) c = getchar();
    bool neg = false;
    if (c == '-') neg = true;
    for (; c < 48 || c > 57; c = getchar());
    for (; c > 47 && c < 58; c = getchar()) x = (x << 3) + (x << 1) + (c & 15);
    if (neg) x = -x;
}
 
template<typename T> void out(T n, char CC) {
    if (n < 0) {
        putchar('-');
        n *= -1;
    }
    char snum[65];
    int i = 0;
    do {
        snum[i++] = n % 10 + '0';
        n /= 10;
    } while (n);
    i = i - 1;
    while (i >= 0) putchar(snum[i--]);
    putchar(CC);
}
/** END OF DESPERATE OPTIMIZATION **/
 
using ll = long long;
using ld = long double;
 
inline ll sq(ll x) { return x * x; }
 
ll dist(pair<ll, ll> a, pair<ll, ll> b) {
  return sq(a.first - b.first) + sq(a.second - b.second);
}
 
int n;
vector<pair<ll, ll>> ve, d;
vector<vector<ll>> t;
 
void build(int v, int s, int e) {
  if(s == e) {
    t[v] = vector<ll>(1, d[s - 1].second);
    return;
  }
  int mid = (s + e) >> 1;
  build(v << 1, s, mid);
  build(v << 1 | 1, mid + 1, e);
  merge(t[v << 1].begin(), t[v << 1].end(), t[v << 1 | 1].begin(), t[v << 1 | 1].end(), back_inserter(t[v]));
}
 
int que_kecil(int v, int s, int e, int l, int r, ll r2) {
  if(r < s || l > e || l > r) { return 0; }
  if(r >= e && l <= s) {
    int ret = upper_bound(t[v].begin(), t[v].end(), r2) - t[v].begin();
    return ret;
  }
  int mid = (s + e) >> 1;
  return que_kecil(v << 1, s, mid, l, min(r, mid), r2) + que_kecil(v << 1 | 1, mid + 1, e, max(l, mid + 1), r, r2);
} 
 
int que_besar(int v, int s, int e, int l, int r, ll r2) {
  if(r < s || l > e || l > r) { return 0; }
  if(r >= e && l <= s) {
    int ret = lower_bound(t[v].begin(), t[v].end(), r2 + 1) - t[v].begin();
    return (int)t[v].size() - ret;
  }
  int mid = (s + e) >> 1;
  return que_besar(v << 1, s, mid, l, min(r, mid), r2) + que_besar(v << 1 | 1, mid + 1, e, max(l, mid + 1), r, r2);
}
 
void solve(int tc) {
 
  in(n);
  if(n == 0) {
    exit(0);
  }
  t.resize(4 * n + 5);
  
  printf("Case "); out(tc, ':'); printf("\n");
  for(int i = 0; i < n; i++) {
    ll x, y;
    in(x), in(y);
    ve.emplace_back(x, y);
  }
  ll ax, ay, bx, by;
  int q;
  in(ax), in(ay), in(bx), in(by), in(q);
  for(int i = 0; i < n; i++) {
    ll da = dist(ve[i], make_pair(ax, ay));
    ll db = dist(ve[i], make_pair(bx, by));
    d.emplace_back(da, db);
  }
  sort(d.begin(), d.end());
 
  build(1, 1, n);
  while(q--) {
    ll r1, r2;
    in(r1), in(r2);
    r1 = sq(r1), r2 = sq(r2);
    int pos1 = lower_bound(d.begin(), d.end(), make_pair(r1 + 1, -1LL)) - d.begin();
    int pos2 = lower_bound(d.begin(), d.end(), make_pair(r1 + 1, -1LL)) - d.begin();
    int luar = que_besar(1, 1, n, pos2 + 1, n, r2);
    int dalam = que_kecil(1, 1, n, 1, pos1, r2);
    // cerr << luar << ' ' << dalam << '\n';
    out(max(0, luar - dalam), '\n');
  }
 
  for (int i = 0; i < 4 * n + 5; i++)
     t[i].clear();
  t.clear();
  
  d.clear(), ve.clear();
}
 
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
 
  int TC = 1;
  while(1) {
    solve(TC++);
  }
  
  return 0;
}