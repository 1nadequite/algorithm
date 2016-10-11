#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;
int m;
string s;

int ch(char a) {
  return (a - 'a');
}

char in(int i) {
  return (i + 'a');
}

bool check(const vector<int>& b) {
  for (int i = 1; i < b.size(); ++i)
    if (b[i] - b[i - 1] > m) return true;
  return false;
}

void solve(const vector<int>& b, int c) {
  vector<char> ans;
  int last = -1, lastc = -1, i;
  for (i = 0; i < s.size(); ++i) {
    if (ch(s[i]) < c) {
      if (i - last > m) {
        ans.push_back(s[lastc]);
      }
      ans.push_back(s[i]);
      last = i;
    }
    else if (ch(s[i]) == c) {
      if (i - last > m) {
        ans.push_back(s[i]);
        last = lastc;
      }
      lastc = i;
    }
  }
  if (i - last > m) ans.push_back(s[lastc]);
  sort(ans.begin(), ans.end());
  for (auto x: ans)
    cout << x;
  cout << endl;
}

int main() {
  cin >> m >> s;
  int n = s.size();
  for (int i = 0; i < 26; ++i) {
    vector<int> b = {-1};
    for (int j = 0; j < n; ++j)
      if (ch(s[j]) <= i) b.push_back(j);
    b.push_back(n);
    if (check(b)) continue;
    solve(b, i);
    break;
  }

  return 0;
}
