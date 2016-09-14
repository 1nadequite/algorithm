// LCA - least common ancestor
// preproc O(N)
// query   O(log N)
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
typedef long double ld;
const int maxn = 1005;
vector<int> graph[maxn], lca_depth, lca_dfs_list, lca_index(maxn);
bool visited[maxn];
int n, m, position = 0;

template <typename T>
class minimizator {
  public:
    minimizator(size_t n) {
        data_s_.assign(n + 1, 1000000000);
        data_left_.assign(n + 1, 1000000000);
        data_right_.assign(n + 1, 1000000000);
        data_s_idx_.assign(n + 1, 0);
        data_left_idx_.assign(n + 1, 0);
        data_right_idx_.assign(n + 1, 0);
    }

    void add(size_t x, T amount) {
      x++;
      if (data_s_[x] > amount) {
        data_s_[x] = amount;
        data_s_idx_[x] = x - 1;
      }
      for (int i = x; i < data_s_.size(); i += -i & i)
        if (data_left_[i] > amount) {
          data_left_[i] = amount;
          data_left_idx_[i] = x - 1;
        }
      for (int i = x; i > 0; i &= i - 1)
        if (data_right_[i] > amount) {
          data_right_[i] = amount;
          data_right_idx_[i] = x - 1;
        }
    }

    T get(size_t l, size_t r) {
      l++; r++;
      T result = 1000000000, i, index;
      for (i = r; (i & (i - 1)) >= l; i &= i - 1)
        if (result > data_left_[i]) {
          result = data_left_[i];
          index = data_left_idx_[i];
        }
      if (result > data_s_[i]) {
        result = data_s_[i];
        index = data_s_idx_[i];
      }
      for (i = l; (i + (-i & i)) <= r; i += -i & i)
        if (result > data_right_[i]) {
          result = data_right_[i];
          index = data_right_idx_[i];
        }
      return index; // return index
    }

  private:
    vector<T> data_s_;
    vector<T> data_left_;
    vector<T> data_right_;
    // save position min element
    vector<T> data_s_idx_;
    vector<T> data_left_idx_;
    vector<T> data_right_idx_;
};

void lca_dfs(int v, int h = 0) {
    visited[v] = true;
    lca_index[v] = position; // firts input vertex in dfs_list
    position++;
    lca_depth.push_back(h); // input in current depth
    lca_dfs_list.push_back(v); // input in current vertex
    for (const auto& u : graph[v]) {
        if (!visited[u]) {
            lca_dfs(u, h + 1);
            position++;
            lca_depth.push_back(h); // output from curretn depth
            lca_dfs_list.push_back(v); // output from currenr vertex
        }
    }
}

int lca(minimizator<int>& mn, int u, int v) {
    if (lca_index[u] < lca_index[v]) return lca_dfs_list[ mn.get(lca_index[u], lca_index[v]) ];
    else return lca_dfs_list[ mn.get(lca_index[v], lca_index[u]) ];
}

int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) visited[i] = false;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }
    lca_dfs(5); // root

    int lca_n = lca_dfs_list.size();
    minimizator<int> mn(lca_n);
    // inizialization minimizator with lca depth
    for (int i = 0; i < lca_n; ++i)
        mn.add(i, lca_depth[i]);

    cout << lca(mn, 7, 8) << endl;
    cout << lca(mn, 3, 7) << endl;
    cout << lca(mn, 3, 5) << endl;
    cout << lca(mn, 3, 1) << endl;

    return 0;
}




int s[2*maxn], l[2*maxn], r[2*maxn];
int pl[2*maxn], pr[2*maxn];
int n;


 
void add(int x, int z) {
 if (s[x]>z) s[x]=z;
 for (int i=x; i<=2*n; i+=-i&i)
  if (l[i]>z) l[i]=z, pl[i]=x;
 for (int i=x; i>=1; i&=i-1)
  if (r[i]>z) r[i]=z, pr[i]=x;
}
 
int get(int x, int y) {
 int res=inf, p=-1, i;
 for (i=y; (i&(i-1))>=x; i&=i-1)
  if (res>l[i]) res=l[i], p=pl[i];
 if (res>s[i]) res=s[i], p=i;
 for (i=x; (i+(-i&i))<=y; i+=-i&i)
  if (res>r[i]) res=r[i], p=pr[i];
 return p;
}
 
 
int path[2*maxn], first[maxn], prev[maxn], previd[maxn];
int m;
 
 
void dfs(int x, int p, int pid, int d) {
 path[m]=x;
 first[x]=m; 
 prev[x]=p;
 previd[x]=pid;
 add(m++, d);
 for (int i=0; i<g[x].size(); ++i) if (g[x][i]!=p) {
  dfs(g[x][i], x, id[x][i], d+1);
  path[m]=x;
  add(m++, d);
 }
}
 
int lca(int x, int y) {
 x=first[x], y=first[y];
 if (x>y) swap(x, y);
 return path[get(x, y)];
}
