#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class summator {
  public:
    summator(size_t n) : data_(n + 1) {}

    void add(size_t i, T amount) {
      for (i++; i <= data_.size(); i += -i & i) {
        data_[i] += amount;
      }
    }

    T sum(size_t l, size_t r) {
      T result = 0;
      for (r++; r > 0; r &= r-1)
        result += data_[r];
      for (; l > 0; l &= l-1)
        result -= data_[l];
      return result;
    }
  private:
    vector<T> data_;
};

int main() {
  summator<int> sum(10); // indexing from [0, n-1], like in vector

  // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  for (int i = 0; i < 10; ++i)
    sum.add(i, i); // add elements in summator

  cout << sum.sum(0, 3) << endl; // sum [0, 3] = 6
  cout << sum.sum(3, 6) << endl; // sum [3, 6] = 18

  return 0;
}
