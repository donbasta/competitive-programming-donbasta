#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif

  int tc;
  cin >> tc;
  while(tc--) {
    int n;
    cin >> n;
    if(n % 4 == 0) {
      cout << "YES";
    } else {
      cout << "NO";
    }
    cout << '\n';
  }

  return 0;
}
