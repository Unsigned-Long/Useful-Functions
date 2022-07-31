#include "artwork/logger/logger.h"
#include "artwork/timer/timer.h"
#include <algorithm>
#include <random>
#include <vector>

/**
 * @brief find k best elem in a vector
 *
 * @tparam Ty the element type
 * @tparam Comp the compare function type
 * @param vec the data vector
 * @param k the k number
 * @param comp the compare function
 * @return std::vector<std::size_t> the k best elements
 */
template <typename Ty, typename Comp>
std::vector<std::size_t> kBest(const std::vector<Ty> &vec, std::size_t k, Comp comp) {
  // init the best k vector
  std::vector<std::size_t> bestVec(k);
  for (int i = 0; i != k; ++i) {
    bestVec[i] = i;
  }
  std::sort(bestVec.begin(), bestVec.end(), [&vec, &comp](auto idx1, auto idx2) {
    return comp(vec[idx1], vec[idx2]);
  });
  // for each
  for (int i = bestVec.size(); i != vec.size(); ++i) {
    const auto &curElem = vec[i];
    // find cur element pos in the best vector
    std::size_t p = 0;
    for (; p != bestVec.size(); ++p) {
      if (comp(curElem, vec[bestVec[p]])) {
        break;
      }
    }
    if (p == bestVec.size()) {
      continue;
    }
    // insert
    for (int j = bestVec.size() - 1; j != p; --j) {
      bestVec[j] = bestVec[j - 1];
    }
    bestVec[p] = i;
  }
  return bestVec;
}

int main(int argc, char const *argv[]) {
  {
    std::vector<int> vec{1, 4, 2, 5, 8, 3, 6, 9, 2, 10};
    auto best = kBest(vec, 4, [](int i1, int i2) {
      return i1 > i2;
    });
    for (const auto &i : best) {
      LOG_VAR(vec[i]);
    }
  }
  {
    ns_timer::Timer timer;
    std::vector<float> vec(1000000);
    std::default_random_engine e;
    std::uniform_real_distribution<> u(0.0, 100.0);
    for (int i = 0; i != vec.size(); ++i) {
      vec[i] = u(e);
    }
    timer.re_start();
    auto best = kBest(vec, 10, [](float i1, float i2) {
      return i1 > i2;
    });
    LOG_VAR(timer.last_elapsed("kBest"));
    for (const auto &i : best) {
      LOG_VAR(vec[i]);
    }
    timer.re_start();
    std::sort(vec.begin(), vec.end(), [](float i1, float i2) { return i1 > i2; });
    LOG_VAR(timer.last_elapsed("sort"));
    for (int i = 0; i != best.size(); ++i) {
      LOG_VAR(vec[i]);
    }
  }
  return 0;
}
