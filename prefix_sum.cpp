#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
vector<ll> a(maxn), pref(maxn);
int n;

void precalc() {
  pref[0] = 0;
  for (int i = 0; i < n; ++i)
    pref[i + 1] = pref[i] + a[i];
}

ll query(int l, int r) {
  if (l > 0) return pref[r + 1] - pref[l];
  else return pref[r + 1];
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];

  precalc();

  cout << query(1, 4) << endl;
  cout << query(0, 5) << endl;
  cout << query(4, 9) << endl;
  cout << query(0, 9) << endl;

  return 0;
}
