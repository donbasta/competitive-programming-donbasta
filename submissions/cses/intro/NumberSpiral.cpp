#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

void solve() {
  ll x, y;
  cin >> x >> y;
  ll mx = max(x, y);
  ll ans;
  if(mx & 1) {
    ans = (mx - 1) * (mx - 1) + 1 + abs(x - mx) + abs(y - 1); 
  } else {
    ans = (mx - 1) * (mx - 1) + 1 + abs(x - 1) + abs(y - mx);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int TC = 1;
  cin >> TC;
  for(int i = 1; i <= TC; i++) {
    solve();
  }
  
  return 0;
}