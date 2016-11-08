// Huffman code
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
map<char, string> ans;

struct node {
  int chan;
  char sym;
  node *left;
  node *right;
  node(int c, char s) : chan(c), sym(s), left(NULL), right(NULL) {}
};

void createHuffTree(node *root, string s) {
  if (root->sym != ' ') {
    if (!s.size()) ans[root->sym] = '0';
    else ans[root->sym] = s;
    return;
  }
  string t = s + '0';
  createHuffTree(root->left, t);
  t = s + '1';
  createHuffTree(root->right, t);
}

int main() {
  string s; cin >> s;
  map<char, int> m;
  int n = s.size();
  for (int i = 0; i < n; ++i) m[s[i]]++;
  priority_queue<pair<int, node*>, vector<pair<int, node*>>, greater<pair<int, node*>>> huff_queue;
  for (auto& x: m) {
    node *nn = new node(x.second, x.first);
    huff_queue.push({x.second, nn});
  }
  while (huff_queue.size() > 1) {
    auto a1 = huff_queue.top();
    huff_queue.pop();
    auto a2 = huff_queue.top();
    huff_queue.pop();
    node *nn = new node(a1.first + a2.first, ' ');
    nn->left = a1.second;
    nn->right = a2.second;
    huff_queue.push({a1.first + a2.first, nn});
  }
  createHuffTree(huff_queue.top().second, "");

  string s_ans;
  for (auto& x: s)
    s_ans += ans[x];
  cout << ans.size() << ' ' << s_ans.size() << endl;
  for (auto& x: ans)
    cout << x.first << ": " << x.second << endl;
  cout << s_ans << endl;

  return 0;
}
