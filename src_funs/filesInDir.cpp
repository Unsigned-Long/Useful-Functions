#include <iostream>
#include <vector>
#include <filesystem>

/**
 * \brief a function to get all the filenames in the directory
 * \param directory the directory 
 * \return the filenames in the directory
 */
std::vector<std::string> filesInDir(const std::string &directory)
{
    std::vector<std::string> files;
    for (const auto &elem : std::filesystem::directory_iterator(directory))
        files.push_back(std::filesystem::canonical(elem.path()).c_str());
    return files;
}

int main(int argc, char const *argv[])
{
    auto ls = filesInDir("../src_funs");
    for (const auto &file : ls)
        std::cout << file << std::endl;
    return 0;
}
