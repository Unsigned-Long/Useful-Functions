#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * \brief a function to split a string to some string elements according the splitor
 * \param str the string to be splited
 * \param splitor the splitor char
 * \param ignoreEmpty whether ignoring the empty string element or not
 */
std::vector<std::string> split(const std::string &str, char splitor, bool ignoreEmpty = true)
{
    std::vector<std::string> vec;
    auto iter = str.cbegin();
    while (true)
    {
        auto pos = std::find(iter, str.cend(), splitor);
        auto elem = std::string(iter, pos);
        if ((!ignoreEmpty) || (ignoreEmpty && !elem.empty()))
            vec.push_back(elem);
        if (pos == str.cend())
            break;
        iter = ++pos;
    }
    return vec;
}

int main(int argc, char const *argv[])
{
    auto vec = split(":12:353:4564:456:", ':', true);
    for (const auto &elem : vec)
        std::cout << elem << std::endl;
    return 0;
}
