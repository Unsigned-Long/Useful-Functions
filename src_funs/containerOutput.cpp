#include <iostream>

#include <unordered_map>
#include <map>

#include <unordered_set>
#include <set>

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <array>

#pragma region output for container

/**
 * @brief the splitor [std::string]
 */
static std::string splitor(", ");

enum class SplitorType
{
    COMMA_SPACE,
    COMMA_ENDL_SPACE,
    SPACE_VL_SPACE
};

static const std::unordered_map<SplitorType, std::string> ssMap({{SplitorType::COMMA_SPACE, ", "},
                                                                 {SplitorType::COMMA_ENDL_SPACE, ",\n "},
                                                                 {SplitorType::SPACE_VL_SPACE, " | "}});

void setSplitor(const std::string &sp)
{
    splitor = sp;
}

void setSplitor(SplitorType spType)
{
    splitor = ssMap.at(spType);
}

/**
 * @brief overload the operator '<<' for std::pair
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::pair<Key, Val> &p)
{
    os << "{'key': " << p.first << ", 'val': " << p.second << '}';
    return os;
}

/**
 * @brief output format for container
 */
template <typename ConType>
std::ostream &outputCon(std::ostream &os, const ConType &s)
{
    os << '[';
    auto iter = s.cbegin();
    for (; iter != (--s.cend()); ++iter)
        os << *iter << splitor;
    os << *iter << ']';
    return os;
}

#pragma endregion

#pragma region map

/**
 * @brief overload the operator '<<' for std::map
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::map<Key, Val> &m)
{
    return outputCon(os, m);
}

/**
 * @brief overload the operator '<<' for std::multimap
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::multimap<Key, Val> &m)
{
    return outputCon(os, m);
}

/**
 * @brief overload the operator '<<' for std::unordered_map
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<Key, Val> &m)
{
    return outputCon(os, m);
}

/**
 * @brief overload the operator '<<' for std::unordered_multimap
 */
template <typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_multimap<Key, Val> &m)
{
    return outputCon(os, m);
}

#pragma endregion

#pragma region set

/**
 * @brief overload the operator '<<' for std::set
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::set<Val> &s)
{
    return outputCon(os, s);
}

/**
 * @brief overload the operator '<<' for std::unordered_set
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<Val> &s)
{
    return outputCon(os, s);
}

/**
 * @brief overload the operator '<<' for std::multiset
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::multiset<Val> &s)
{
    return outputCon(os, s);
}

/**
 * @brief overload the operator '<<' for std::unordered_multiset
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::unordered_multiset<Val> &s)
{
    return outputCon(os, s);
}

#pragma endregion

#pragma region seq cons

/**
 * @brief overload the operator '<<' for std::vector
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::vector<Val> &s)
{
    return outputCon(os, s);
}

/**
 * @brief overload the operator '<<' for std::list
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::list<Val> &s)
{
    return outputCon(os, s);
}

/**
 * @brief overload the operator '<<' for std::deque
 */
template <typename Val>
std::ostream &operator<<(std::ostream &os, const std::deque<Val> &s)
{
    return outputCon(os, s);
}

/**
 * @brief overload the operator '<<' for std::array
 */
template <typename Val, std::size_t Size>
std::ostream &operator<<(std::ostream &os, const std::array<Val, Size> &s)
{
    os << '[';
    for (int i = 0; i != s.size() - 1; ++i)
        os << s[i] << splitor;
    os << s.back() << ']';
    return os;
}

#pragma endregion

#pragma region multi output

std::ostream &multiOutput(std::ostream &os)
{
    return os;
}

template <typename _Ty>
std::ostream &multiOutput(std::ostream &os, const _Ty &arg)
{
    os << arg << '\n';
    return os;
}

template <typename _Ty1, typename... _Ty2>
std::ostream &multiOutput(std::ostream &os, const _Ty1 arg, const _Ty2... args)
{
    os << arg << splitor;
    multiOutput(os, args...);
    return os;
}

#pragma endregion

int main(int argc, char const *argv[])
{
    std::map<int, std::string> isMap({std::make_pair(0, "hello"),
                                      std::make_pair(2, "world"),
                                      std::make_pair(3, "cpp"),
                                      std::make_pair(4, "python")});

    std::set<int> iSet({1, 2, 5, 7, 2, 6, 68});

    std::vector<int> iVec({1, 2, 5, 7, 2, 6, 68});
    std::list<int> iLis({1, 2, 5, 7, 2, 6, 68});
    std::deque<int> iDeq({1, 2, 5, 7, 2, 6, 68});
    std::array<int, 7> iAry{1, 2, 5, 7, 2, 6, 68};

    std::cout << isMap << std::endl;
    std::cout << iSet << std::endl;
    std::cout << iVec << std::endl;
    setSplitor(SplitorType::SPACE_VL_SPACE);
    std::cout << iLis << std::endl;
    setSplitor(SplitorType::COMMA_SPACE);

    std::cout << iDeq << std::endl;
    std::cout << iAry << std::endl;
    setSplitor(SplitorType::COMMA_ENDL_SPACE);

    multiOutput(std::cout, iAry, isMap, iAry);

    return 0;
}
