#include "google_btree/btree_set.h"
#include <algorithm>
#include <set>
#include <unordered_set>

using Duration = std::chrono::duration<double>;

auto Now = [] { return std::chrono::high_resolution_clock::now(); };

// Sequential insert
template <class IntegerSet>
Duration SequentialInsertTestImpl(IntegerSet set, int n) {
  auto start = Now();
  for (int i = 0; i < n; ++i) {
    set.insert(i);
  }
  return Now() - start;
}

template <class IntegerSet>
Duration SequentialInsertTest(IntegerSet set, int n, int k = 32) {
  auto result = SequentialInsertTestImpl(set, n);
  for (int i = 1; i < k; ++i) {
    result = std::min(result, SequentialInsertTestImpl(set, n));
  }
  return result;
}

int main() {
  for (int n = 64; n <= 1024 * 1024; n += n) {
    std::set<int> set;
    std::unordered_set<int> unordered_set_reserved;
    std::unordered_set<int> unordered_set;
    btree::btree_set<int> btree_set;
    unordered_set_reserved.reserve(n);
    std::cout
        << n << '\t' << SequentialInsertTest(std::move(btree_set), n).count()
        << '\t'
        << SequentialInsertTest(std::move(unordered_set_reserved), n).count()
        << '\t' << SequentialInsertTest(std::move(unordered_set), n).count()
        << '\t' << SequentialInsertTest(std::move(set), n).count() << std::endl;
  }
  return 0;
}
