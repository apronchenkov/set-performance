#include "google_btree/btree_set.h"
#include <algorithm>
#include <random>
#include <set>
#include <unordered_set>

using Duration = std::chrono::duration<double>;

auto Now = [] { return std::chrono::high_resolution_clock::now(); };

// Sequential insert
template <class IntegerSet>
Duration RandomInsertTestImpl(IntegerSet set, int n) {
  std::mt19937 random(5757);
  std::uniform_int_distribution<> distribution;
  auto start = Now();
  for (int i = 0; i < n; ++i) {
    set.insert(distribution(random));
  }
  return Now() - start;
}

template <class IntegerSet>
Duration RandomInsertTest(IntegerSet set, int n, int k = 32) {
  auto result = RandomInsertTestImpl(set, n);
  for (int i = 1; i < k; ++i) {
    result = std::min(result, RandomInsertTestImpl(set, n));
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
    std::cout << n << '\t' << RandomInsertTest(std::move(btree_set), n).count()
              << '\t'
              << RandomInsertTest(std::move(unordered_set_reserved), n).count()
              << '\t' << RandomInsertTest(std::move(unordered_set), n).count()
              << '\t' << RandomInsertTest(std::move(set), n).count()
              << std::endl;
  }
  return 0;
}
