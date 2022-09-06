#include "artwork/logger/logger.h"

/**
 * trim a string with target char 'c'
 * @param str the target string
 * @param c the char to trimmed
 * @return the trimmed string
 */
std::string trim(const std::string &str, char c = ' ') {
  auto p1 = str.find_first_not_of(c);
  auto p2 = str.find_last_not_of(c);
  if (p1 != std::string::npos && p2 != std::string::npos) {
    return str.substr(p1, p2 - p1 + 1);
  } else {
    return {};
  }
}

int main() {
  {
    std::string str = "..123..";
    auto result = trim(str, '.');
    LOG_VAR(result, result.size());
  }
  {
    std::string str = "  123  ";
    auto result = trim(str, ' ');
    LOG_VAR(result, result.size());
  }

  return 0;
}