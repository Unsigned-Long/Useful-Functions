#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * @brief output format for containers in the STL
 * [1] std::pair
 * [2] std::map std::multimap std::unordered_map std::unordered_multimap
 * [3] std::set std::multiset std::unordered_set std::unordered_multiset
 * [4] std::vector std::list std::deque std::array
 * [5] struct
 */

#pragma region output for container

/**
 * @brief params to control
 * @param splitor the splitor to split the elements
 * @param firName the describe name for the first element of the std::pair
 * @param sedName the describe name for the second element of the std::pair
 */
static std::string splitor(", ");
static std::string firName("fir");
static std::string sedName("sed");

/**
 * @brief Set the splitor
 */
static void setSplitor(const std::string &sp) { splitor = sp; }

/**
 * @brief Set the firName and sedName
 */
static void setFirSedName(const std::string &firstName,
                          const std::string &secondName) {
  firName = firstName, sedName = secondName;
}

/**
 * @brief overload the operator '<<' for std::pair
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::pair<Key, Val> &p) {
  os << "{'" + firName + "': " << p.first << ", '" + sedName + "': " << p.second
     << '}';
  return os;
}

/**
 * @brief output format for ordered container
 */
template <typename ConType>
std::ostream &orderedConer(std::ostream &os, const ConType &c) {
  os << '[';
  if (c.empty()) {
    os << "(empty)]";
    return os;
  }
  auto iter = c.cbegin();
  for (; iter != (--c.cend()); ++iter) os << *iter << splitor;
  os << *iter << ']';
  return os;
}

/**
 * @brief output format for unordered container
 */
template <typename ConType>
std::ostream &unorderedConer(std::ostream &os, const ConType &c) {
  os << '[';
  if (c.empty()) {
    os << "(empty)]";
    return os;
  }
  std::stringstream stream;
  for (const auto &elem : c) stream << elem << splitor;
  std::string str = stream.str();
  os << std::string_view(str.c_str(), str.size() - splitor.size()) << ']';
  return os;
}

#pragma endregion

#pragma region map

/**
 * @brief overload the operator '<<' for std::map
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::map<Key, Val> &m) {
  return orderedConer(os, m);
}

/**
 * @brief overload the operator '<<' for std::multimap
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::multimap<Key, Val> &m) {
  return orderedConer(os, m);
}

/**
 * @brief overload the operator '<<' for std::unordered_map
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_map<Key, Val> &m) {
  return unorderedConer(os, m);
}

/**
 * @brief overload the operator '<<' for std::unordered_multimap
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_multimap<Key, Val> &m) {
  return unorderedConer(os, m);
}

#pragma endregion

#pragma region set

/**
 * @brief overload the operator '<<' for std::set
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::set<Val> &s) {
  return orderedConer(os, s);
}

/**
 * @brief overload the operator '<<' for std::unordered_set
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<Val> &s) {
  return unorderedConer(os, s);
}

/**
 * @brief overload the operator '<<' for std::multiset
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::multiset<Val> &s) {
  return orderedConer(os, s);
}

/**
 * @brief overload the operator '<<' for std::unordered_multiset
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_multiset<Val> &s) {
  return unorderedConer(os, s);
}

#pragma endregion

#pragma region seq cons

/**
 * @brief overload the operator '<<' for std::vector
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::vector<Val> &s) {
  return orderedConer(os, s);
}

/**
 * @brief overload the operator '<<' for std::list
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::list<Val> &s) {
  return orderedConer(os, s);
}

/**
 * @brief overload the operator '<<' for std::deque
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::deque<Val> &s) {
  return orderedConer(os, s);
}

/**
 * @brief overload the operator '<<' for std::array
 */
template <typename Val, std::size_t Size>
std::ostream &operator<<(std::ostream &os, const std::array<Val, Size> &s) {
  os << '[';
  for (int i = 0; i != s.size() - 1; ++i) os << s[i] << splitor;
  os << s.back() << ']';
  return os;
}

/**
 * @brief overload the operator '<<' for std::stack
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::stack<Val> &s) {
  if (s.empty()) {
    os << "[(empty)]";
    return os;
  }
  os << "[(top) ";
  auto cs = s;
  while (cs.size() != 1) {
    os << cs.top() << splitor;
    cs.pop();
  }
  os << cs.top() << "]";
  return os;
}

/**
 * @brief overload the operator '<<' for std::queue
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::queue<Val> &q) {
  if (q.empty()) {
    os << "[(empty)]";
    return os;
  }
  os << "[(front) ";
  auto cq = q;
  while (cq.size() != 1) {
    os << cq.front() << splitor;
    cq.pop();
  }
  os << cq.front() << "]";
  return os;
}
#pragma endregion

#pragma region structure output

// std::ostream &operator<<(std::ostream &os, const ObjType &obj)
// {
//     os << '{';
//     os << "'member1': " << obj._member1 << ", ";
//     os << "'member2': " << obj._member2 << ", ";
//     os << "'member3': " << obj._member3 << ", ";
//     os << "'member4': " << obj._member4;
//     os << '}';
//     return os;
// }

#pragma endregion

int main(int argc, char const *argv[]) {
  std::unordered_map<int, std::string> isMap;
  isMap.insert(std::make_pair(0, "hello"));
  isMap.insert(std::make_pair(2, "world"));
  isMap.insert(std::make_pair(3, "cpp"));
  isMap.insert(std::make_pair(4, "python"));

  std::set<int> iSet({1, 2, 5, 7, 2, 6, 68});
  std::vector<int> iVec({1, 2, 5, 7, 2, 6, 68});
  std::list<int> iLis({1, 2, 5, 7, 2, 6, 68});
  std::deque<int> iDeq({1, 2, 5, 7, 2, 6, 68});
  std::array<int, 7> iAry{1, 2, 5, 7, 2, 6, 68};

  std::cout << "   Map: " << isMap << std::endl;
  setFirSedName("intVal", "strVal");
  std::cout << "   Map: " << isMap << std::endl;
  std::cout << "   Set: " << iSet << std::endl;
  std::cout << "Vector: " << iVec << std::endl;
  std::cout << "Vector: " << std::vector<int>() << std::endl;
  std::cout << "  List: " << iLis << std::endl;
  std::cout << " Deque: " << iDeq << std::endl;
  std::cout << " Array: " << iAry << std::endl;

  std::stack<int> sta;
  std::cout << " stack: " << sta << std::endl;
  sta.push(1), sta.push(4), sta.push(7), sta.push(3);
  std::cout << " stack: " << sta << std::endl;

  std::queue<int> que;
  que.push(1), que.push(4), que.push(7);
  std::cout << " queue: " << que << std::endl;

  que.push(3);
  std::cout << " queue: " << que << std::endl;
  return 0;
}
