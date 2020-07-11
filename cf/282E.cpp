#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

const int N = 1e5 + 69;
const int M = 40;

int n;
vector<ll> pre;

ll solve2(int bit, int l1, int r1, int l2, int r2, ll find) {
  if(bit < 0 || l1 >= r1 || l2 >= r2)
    return 0;
  int on = ((find >> bit) & 1);
  int mid1 = l1, mid2 = l2;
  ll temp;
  while(mid1 < r1 && !((pre[mid1] >> bit) & 1))
    mid1++;
  while(mid2 < r2 && !((pre[mid2] >> bit) & 1))
    mid2++;
  if(on) {
    ll x = solve2(bit - 1, l1, mid1, l2, mid2, find);
    ll y = solve2(bit - 1, mid1, r1, mid2, r2, find);
    if((!((l1 >= mid1) && (mid2 >= r2))) && (!((mid1 >= r1) && (l2 >= mid2))))
      temp = max(x, y) + (1LL << bit);
    else
      temp = 0;
  } else {
    ll x = solve2(bit - 1, l1, mid1, mid2, r2, find);
    ll y = solve2(bit - 1, mid1, r1, l2, mid2, find);
    if((!((l1 >= mid1) && (l2 >= mid2))) && (!((mid1 >= r1) && (mid2 >= r2))))
      temp = (1LL << bit) + max(x, y);
    else
      temp = 0;
  }
  return temp;
}

ll solve(int bit, int l, int r, ll find) {
  if(bit < 0)
    return 0;
  if(l >= r)
    return 0;
  int on = ((find >> bit) & 1);
  int mid = l;
  ll temp;
  while(mid < r && !((pre[mid] >> bit) & 1))
    mid++;
  if(on) {
    ll x = solve(bit - 1, l, mid, find);
    ll y = solve(bit - 1, mid, r, find);
    cerr << bit << ' ' << x << ' ' << y << " :D\n";
    temp = max(x, y);
    // if((!(l >= mid)) && !(mid >= r))
    temp += (1LL << bit);
  } else {
    if((l >= mid) || (mid >= r)) {
      temp = solve(bit - 1, l, r, find);
    } else {
      temp = (1LL << bit) + solve2(bit - 1, l, mid, mid, r, find);
      cerr << l << ' ' << mid << ' ' << r << " :(\n";
    }
  }
  return temp;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  cin >> n;
  pre.assign(n + 1, 0);
  for(int i = 1; i <= n; i++) {
    ll t;
    cin >> t;
    pre[i] = pre[i - 1] ^ t;
  }
  if(n == 1) {
    cout << pre[n] << '\n';
    return 0;
  }
  // for(auto i : pre) cerr << i << ' ';
  // cerr << '\n';
  ll lol = pre[n];
  sort(pre.begin(), pre.end());
  // for(auto i : pre) cerr << i << ' ';
  ll ans = solve(M, 0, n + 1, lol);
  cout << ans << '\n';
  return 0;
}
