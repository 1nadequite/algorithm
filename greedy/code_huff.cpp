// Huffman code
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
map<char, string> ans;

int main() {
  string s; cin >> s;
  map<char, int> m;
  int n = s.size();
  for (int i = 0; i < n; ++i) m[s[i]]++;

  if (m.size() == 1) {
    cout << m.size() << ' ' << s.size() << endl;
    cout << s[0] << ": " << 0 << endl;
    for (int i = 0; i < n; ++i)
      cout << 0;
    cout << endl;
    return 0;
  }

  priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> huff_queue;
  for (auto &x: m)
    huff_queue.push({x.second, string(1, x.first)});

  while (huff_queue.size() > 1) {
    auto a1 = huff_queue.top();
    huff_queue.pop();
    auto a2 = huff_queue.top();
    huff_queue.pop();

    for (auto &c: a1.second)
      ans[c] += '0';
    for (auto &c: a2.second)
      ans[c] += '1';
    huff_queue.push({a1.first + a2.first, a1.second + a2.second});
  }
  for (auto &x: ans)
    reverse(x.second.begin(), x.second.end());

  string s_ans;
  for (auto& x: s)
    s_ans += ans[x];
  cout << ans.size() << ' ' << s_ans.size() << endl;
  for (auto& x: ans)
    cout << x.first << ": " << x.second << endl;
  cout << s_ans << endl;

  return 0;
}
