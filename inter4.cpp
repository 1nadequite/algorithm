#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string sum(const string& a, const string& b, int base) {
  string s;
  int na = a.size() - 1, nb = b.size() - 1, carry = 0;
  for (; na >= 0 || nb >= 0; --na, --nb) {
    int t = carry + (na >= 0 ? a[na] - '0' : 0) + (nb >= 0 ? b[nb] - '0' : 0);
    s.push_back('0' + t % base);
    carry = t / base;
  }
  if (carry) s.push_back('1');
  reverse(s.begin(), s.end());
  return s;
}

string mult(const string& a, const string& b, int base) {
  string s;
  int na = a.size() - 1, nb = b.size() - 1;
  for (int i = na; i >= 0; --i) {
    string t;
    int k = na - i, carry = 0;
    while (k--) t.push_back('0');

    for (int j = nb; j >= 0; --j) {
      int c = (a[i] - '0') * (b[j] - '0') + carry;
      t.push_back('0' + c % base);
      carry = c / base;
    }
    if (carry) t.push_back(carry + '0');

    if (s.empty()) s = t;
    else {
      int ns = s.size(), nt = t.size();
      string g;
      carry = 0;
      for (int l = 0, m = 0; l < ns || m < nt; ++l, ++m) {
        int c = carry + (l < ns ? s[l] - '0' : 0) + (m < nt ? t[m] - '0' : 0);
        g.push_back('0' + c % base);
        carry = c / base;
      }
      if (carry) g.push_back(carry + '0');
      s = g;
    }
  }
  reverse(s.begin(), s.end());
  return s;
}

int main() {
  string a = "12301", b = "1300";
  cout << sum(a, b, 4) << endl;
  cout << mult(a, b, 4) << endl;

  return 0;
}
