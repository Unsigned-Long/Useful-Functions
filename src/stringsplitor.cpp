#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ns_v1 {
  /**
   * @brief a function to split a string to some string elements according the splitor
   * @param str the string to be splited
   * @param splitor the splitor char
   * @param ignoreEmpty whether ignoring the empty string element or not
   * @return the splited string vector
   */
  std::vector<std::string> __split__(const std::string &str, char splitor, bool ignoreEmpty = true) {
    std::vector<std::string> vec;
    auto iter = str.cbegin();
    while (true) {
      auto pos = std::find(iter, str.cend(), splitor);
      auto elem = std::string(iter, pos);
      if (!(elem.empty() && ignoreEmpty)) {
        vec.push_back(elem);
      }
      if (pos == str.cend()) {
        break;
      }
      iter = ++pos;
    }
    return vec;
  }
} // namespace ns_v1

namespace ns_v2 {
  /**
   * @brief a function to split a string to some string elements according the splitor
   * @param str the string to be splited
   * @param splitor the splitor char
   * @param ignoreEmpty whether ignoring the empty string element or not
   * @return the splited string vector
   */
  std::vector<std::string> __split__(const std::string &str, char splitor, bool ignoreEmpty = true) {
    std::vector<std::string> vec;
    std::string elem;
    std::stringstream stream;
    stream << str;
    while (std::getline(stream, elem, splitor)) {
      if (elem.empty() && ignoreEmpty) {
        continue;
      }
      vec.push_back(elem);
    }
    return vec;
  }
} // namespace ns_v2

/**
 * @brief a function to split a string to some string elements according the splitor
 *
 * @param str the string to be splited
 * @param splitor the splitor char
 * @param ignoreEmpty whether ignoring the empty string element or not
 *
 * @return the splited string vector
 */
static std::string __combine__(const std::vector<std::string> &strVec, char splitor, bool ignoreEmpty = false) {
  std::stringstream stream;
  for (const auto &elem : strVec) {
    if (elem.empty() && ignoreEmpty) {
      continue;
    }
    stream << elem << splitor;
  }
  std::string str = stream.str();
  str.pop_back();
  return str;
}

int main(int argc, char const *argv[]) {
  {
    auto vec = ns_v1::__split__("gfc,,0,,,0,,,,1.000,234,6,787,78768,67000000000E+00", ',', true);
    for (const auto &elem : vec)
      std::cout << elem << std::endl;
  }
  std::cout << std::string(20, '-') << std::endl;

  {
    auto vec = ns_v2::__split__("gfc,,0,,,0,,,,1.000,234,6,787,78768,67000000000E+00", ',', true);
    for (const auto &elem : vec)
      std::cout << elem << std::endl;
  }
  {
    auto str = ::__combine__({"1", "2", "12d"}, ',', false);
    std::cout << str << std::endl;
  }
  return 0;
}
