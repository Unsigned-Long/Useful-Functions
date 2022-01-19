#include <iostream>
#include <vector>
#include <algorithm>

struct Info
{
private:
    uint _id;

public:
    /**
     * @brief Construct a new Info object
     */
    Info(const uint &id)
        : _id(id) {}

    inline uint &id() { return this->_id; }
    inline const uint &id() const { return this->_id; }
};

/**
 * @brief pair{MemName, MemType}
 */
using MemInfo = std::pair<std::string, std::string>;

MemInfo split(const std::string &str)
{
    MemInfo info;
    auto pos = str.find_first_of(':');
    info.first = str.substr(0, pos);
    info.second = str.substr(pos + 1);
    return info;
}

void genStruct(const std::string &structName, const std::vector<MemInfo> &info)
{
    std::cout << "struct " + structName << std::endl;
    std::cout << "{" << std::endl;
    std::cout << "private:" << std::endl;
    std::cout << "    /**\n"
                 "     * @brief the members\n"
                 "     */"
              << std::endl;
    for (const auto &elem : info)
        std::cout
            << "    " + elem.second + " _" + elem.first + ";" << std::endl;

    std::cout << "\npublic:" << std::endl;
    std::cout << "    /**\n"
                 "     * @brief Construct a new " +
                     structName + " object\n"
                                  "     */"
              << std::endl;
    std::cout << "    " + structName + '(';
    for (int i = 0; i != info.size() - 1; ++i)
        std::cout << "const " << info.at(i).second << " &" << info.at(i).first << ", ";
    std::cout << "const " << info.back().second << " &" << info.back().first << ')' << std::endl;
    std::cout << "    " << std::string(' ', structName.size());
    std::cout << "    : ";
    for (int i = 0; i != info.size() - 1; ++i)
        std::cout << "_" << info.at(i).first << "(" << info.at(i).first << "), ";
    std::cout << "_" << info.back().first << "(" << info.back().first << ") {}\n\n";

    for (const auto &elem : info)
    {
        std::cout << "    inline " << elem.second << " &" << elem.first << "() { return this->_" + elem.first + "; }\n";
        std::cout << "    inline const " << elem.second << " &" << elem.first << "() const { return this->_" + elem.first + "; }\n\n";
    }

    std::cout << "};" << std::endl;
}

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        std::cout << "This simple program is used to generate cpp 'struct' source code. Here is the usage:\n\n";
        std::cout << "    StructName MemName1:MemType1 [MemName2:MemType2] ...\n\n";
        std::cout << "Here is a example:\n\n";
        std::cout << "    type './usefulFuns Info id:uint' will generate code:\n\n";
        std::cout << "struct Info"
                     "\n{"
                     "\nprivate:"
                     "\n    /**"
                     "\n     * @brief the members"
                     "\n     */"
                     "\n    uint _id;"
                     "\n"
                     "\npublic:"
                     "\n    /**"
                     "\n     * @brief Construct a new Info object"
                     "\n     */"
                     "\n    Info(const uint &id)"
                     "\n        : _id(id) {}"
                     "\n"
                     "\n    inline uint &id() { return this->_id; }"
                     "\n    inline const uint &id() const { return this->_id; }"
                     "\n"
                     "\n};"
                  << std::endl;

        return 0;
    }
    std::string structName = argv[1];

    std::vector<MemInfo> info(argc - 2);

    for (int i = 2; i != argc; ++i)
        info.at(i - 2) = split(argv[i]);
    for (auto &elem : info)
    {
        if (elem.first.at(0) == '_')
            elem.first = elem.first.substr(1);
    }
    genStruct(structName, info);
    return 0;
}