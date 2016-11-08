// Huffman decode
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

struct node {
  char sym;
  node *left;
  node *right;
  node(char s) : sym(s), left(NULL), right(NULL) {}
};

void addInTree(node *root, char c, string s) {
  node *cur = root;
  int pos = 0;
  while (pos < s.size()) {
    char x = s[pos];
    if (x == '0') {
      if (!cur->right) {
        node *nn = new node(' ');
        cur->right = nn;
      }
      cur = cur->right;
    } else {
      if (!cur->left) {
        node *nn = new node(' ');
        cur->left = nn;
      }
      cur = cur->left;
    }
    pos++;
  }
  cur->sym = c;
}

string decode(node *root, string s) {
  node *cur = root;
  string ans;
  int pos = 0;
  while (pos < s.size()) {
    char x = s[pos];
    if (x == '0') cur = cur->right;
    else cur = cur->left;
    if (cur->sym != ' ') {
      ans.push_back(cur->sym);
      cur = root;
    }
    pos++;
  }
  return ans;
}

int main() {
  int k, l; cin >> k >> l;
  map<char, string> m;
  for (int i = 0; i < k; ++i) {
    string t, x; cin >> t >> x;
    m[t[0]] = x;
  }
  string s; cin >> s;

  node *root = new node(' ');
  for (auto& x: m)
    addTree(root, x.first, x.second);

  cout << decode(root, s) << endl;

  return 0;
}

