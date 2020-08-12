#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

void solve() {
  int n;
  ll ans = 0;
  cin >> n;
  vector<int> ar(n);
  for(int i = 0; i < n; i++) {
    cin >> ar[i];
    if(i == 0) continue;
    if(ar[i] < ar[i - 1]) {
      ans += (ar[i - 1] - ar[i]);
      ar[i] = ar[i - 1]; 
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int TC = 1;
  for(int i = 1; i <= TC; i++) {
    solve();
  }
  
  return 0;
}