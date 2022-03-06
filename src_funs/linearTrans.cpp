#include <functional>
#include <iostream>

/**
 * \brief a function to generate a function that maps value from [srcMin, srcMax] to [dstMin, dstMax] linearly
 * \param srcMin the lower boundary of the source value range
 * \param srcMax the upper boundary of the source value range
 * \param dstMin the lower boundary of the target value range
 * \param dstMax the upper boundary of the target value range
 * \return the result value
 */

auto linearTransd(const double &srcMin, const double &srcMax,
                  const double &dstMin, const double &dstMax,
                  const double &val) {
  auto srcRange = srcMax - srcMin;
  auto dstRange = dstMax - dstMin;
  return (val - srcMin) / srcRange * dstRange + dstMin;
}

auto linearTransf(const float &srcMin, const float &srcMax,
                  const float &dstMin, const float &dstMax,
                  const float &val) {
  auto srcRange = srcMax - srcMin;
  auto dstRange = dstMax - dstMin;
  return (val - srcMin) / srcRange * dstRange + dstMin;
}

int main(int argc, char const *argv[]) {
  std::cout << linearTransf(10.0f, 20.0f, 0.0f, 1.0f, 15.0f) << std::endl;
  return 0;
}
