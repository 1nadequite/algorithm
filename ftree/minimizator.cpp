#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class minimizator {
  public:
    minimizator(size_t n) {
        data_s_.assign(n + 1, 1000000000);
        data_left_.assign(n + 1, 1000000000);
        data_right_.assign(n + 1, 1000000000);
    }

    void add(size_t x, T amount) {
      x++;
      if (data_s_[x] > amount)
        data_s_[x] = amount;
      for (int i = x; i < data_s_.size(); i += -i & i)
        if (data_left_[i] > amount)
          data_left_[i] = amount;
      for (int i = x; i > 0; i &= i - 1)
        if (data_right_[i] > amount)
          data_right_[i] = amount;
    }

    T get(size_t l, size_t r) {
      l++; r++;
      T result = 1000000000, i;
      for (i = r; (i & (i - 1)) >= l; i &= i - 1)
        if (result > data_left_[i])
          result = data_left_[i];
      if (result > data_s_[i])
        result = data_s_[i];
      for (i = l; (i + (-i & i)) <= r; i += -i & i)
        if (result > data_right_[i])
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
  minimizator<int> mn(n); // indexing from [0, n-1], like in vector
  vector<int> a = { 1, 2, 3, 2, 1, 4, 6, 2, 7, 1 };

  for (int i = 0; i < n; ++i)
    mn.add(i, a[i]); // add elements in minimizator

  cout << mn.get(0, 3) << endl; // min [0, 3] = 1
  cout << mn.get(0, 9) << endl; // min [0, 9] = 1
  cout << mn.get(5, 7) << endl; // min [5, 7] = 2
  cout << mn.get(8, 8) << endl; // min [8, 8] = 7

  return 0;
}
