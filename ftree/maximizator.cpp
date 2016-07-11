#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class maximizator {
  public:
    maximizator(size_t n) {
        data_s_.assign(n + 1, -1000000000);
        data_left_.assign(n + 1, -1000000000);
        data_right_.assign(n + 1, -1000000000);
    }

    void add(size_t x, T amount) {
      x++;
      if (data_s_[x] < amount)
        data_s_[x] = amount;
      for (int i = x; i < data_s_.size(); i += -i & i)
        if (data_left_[i] < amount)
          data_left_[i] = amount;
      for (int i = x; i > 0; i &= i - 1)
        if (data_right_[i] < amount)
          data_right_[i] = amount;
    }

    T get(size_t l, size_t r) {
      l++; r++;
      T result = -1000000000, i;
      for (i = r; (i & (i - 1)) >= l; i &= i - 1)
        if (result < data_left_[i])
          result = data_left_[i];
      if (result < data_s_[i])
        result = data_s_[i];
      for (i = l; (i + (-i & i)) <= r; i += -i & i)
        if (result < data_right_[i])
          result = data_right_[i];
      return result;
    }

  private:
    // indexing here is from [1, n]
    vector<T> data_s_;
    vector<T> data_left_;
    vector<T> data_right_;
};

int main() {
  int n = 10;
  maximizator<int> mx(n); // indexing from [0, n-1], like in vector
  vector<int> a = { 1, 2, 3, 2, 1, 4, 6, 2, 7, 1 };

  for (int i = 0; i < n; ++i)
    mx.add(i, a[i]); // add elements in maximizator

  cout << mx.get(0, 3) << endl; // max [0, 3] = 3
  cout << mx.get(0, 9) << endl; // max [0, 9] = 7
  cout << mx.get(4, 7) << endl; // max [4, 7] = 6

  return 0;
}
