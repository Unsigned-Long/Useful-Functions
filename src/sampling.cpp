#define FORMAT_VECTOR
#include "artwork/logger/logger.h"
#include <iostream>
#include <random>
#include <vector>

/**
 * @brief sampling the amples without replacement
 *
 * @param num the num of the samples to sampling
 * @param start the start index
 * @param end the end index
 * @param step the step
 * @attention range: [start, end](step) i.e. for [1, 5](2) -> pool: {1, 3, 5}
 * @return std::vector<std::size_t>
 */
std::vector<std::size_t> samplingWoutReplace(std::size_t num, std::size_t start, std::size_t end, std::size_t step = 1) {
  // create the pool for sampling
  std::vector<std::size_t> idxPool((end - start) / step + 1);
  for (int i = 0; i != idxPool.size(); ++i) {
    idxPool.at(i) = start + i * step;
  }
  std::vector<std::size_t> res(num);
  // the engine
  std::default_random_engine engine;
  for (std::size_t i = 0; i != num; ++i) {
    // generate the random index
    std::uniform_int_distribution<std::size_t> ui(0, idxPool.size() - 1);
    std::size_t ridx = ui(engine);
    // record it
    res.at(i) = idxPool.at(ridx);
    // remove it
    idxPool.at(ridx) = idxPool.back();
    idxPool.pop_back();
  }
  return res;
}

/**
 * @brief sampling the amples without replacement
 *
 * @tparam ElemType the element type
 * @param dataVec the data vector
 * @param num the num of the samples to sampling
 * @return std::vector<std::size_t>
 */
template <typename ElemType>
std::vector<std::size_t> samplingWoutReplace(const std::vector<ElemType> &dataVec, std::size_t num) {
  return samplingWoutReplace(num, 0, dataVec.size() - 1, 1);
}

/**
 * @brief sampling the amples without replacement
 *
 * @tparam ElemType the element type
 * @param dataVec the data vector
 * @param num the num of the samples to sampling
 * @return std::vector<ElemType>
 */
template <typename ElemType>
std::vector<ElemType> samplingWoutReplace2(const std::vector<ElemType> &dataVec, std::size_t num) {
  std::vector<std::size_t> res = samplingWoutReplace(dataVec, num);
  std::vector<ElemType> samples(num);
  for (int i = 0; i != num; ++i) {
    samples.at(i) = dataVec.at(res.at(i));
  }
  return samples;
}

/**
 * @brief sampling the amples with replacement
 *
 * @param num the num of the samples to sampling
 * @param start the start index
 * @param end the end index
 * @param step the step
 * @attention range: [start, end](step) i.e. for [1, 5](2) -> pool: {1, 3, 5}
 * @return std::vector<std::size_t>
 */
std::vector<std::size_t> samplingWithReplace(std::size_t num, std::size_t start, std::size_t end, std::size_t step = 1) {
  // create the pool for sampling
  std::vector<std::size_t> idxPool((end - start) / step + 1);
  for (int i = 0; i != idxPool.size(); ++i) {
    idxPool.at(i) = start + i * step;
  }
  std::vector<std::size_t> res(num);
  // the engine
  std::default_random_engine engine;
  std::uniform_int_distribution<std::size_t> ui(0, idxPool.size() - 1);
  for (std::size_t i = 0; i != num; ++i) {
    // generate the random index
    std::size_t ridx = ui(engine);
    // record it
    res.at(i) = idxPool.at(ridx);
  }
  return res;
}

/**
 * @brief sampling the amples with replacement
 *
 * @tparam ElemType the element type
 * @param dataVec the data vector
 * @param num the num of the samples to sampling
 * @return std::vector<std::size_t>
 */
template <typename ElemType>
std::vector<std::size_t> samplingWithReplace(const std::vector<ElemType> &dataVec, std::size_t num) {
  return samplingWithReplace(num, 0, dataVec.size() - 1, 1);
}

/**
 * @brief sampling the amples with replacement
 *
 * @tparam ElemType the element type
 * @param dataVec the data vector
 * @param num the num of the samples to sampling
 * @return std::vector<ElemType>
 */
template <typename ElemType>
std::vector<ElemType> samplingWithReplace2(const std::vector<ElemType> &dataVec, std::size_t num) {
  std::vector<std::size_t> res = samplingWithReplace(dataVec, num);
  std::vector<ElemType> samples(num);
  for (int i = 0; i != num; ++i) {
    samples.at(i) = dataVec.at(res.at(i));
  }
  return samples;
}

int main(int argc, char const *argv[]) {
  std::vector<std::string> names{"Tom", "Jerry", "marry", "Joe", "Bob", "Alice"};
  std::cout << "raw data: " << names << std::endl;
  std::cout << "we want to sample 4 people." << std::endl;
  {
    auto res = ::samplingWoutReplace2(names, 4);
    std::cout << "Sampling Without Replacement: " << res << std::endl;
  }
  {
    auto res = ::samplingWithReplace2(names, 4);
    std::cout << "Sampling With Replacement: " << res << std::endl;
  }
  return 0;
}
