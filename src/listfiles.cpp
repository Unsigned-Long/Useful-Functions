#include <iostream>
#include <vector>
#include <filesystem>
#include <algorithm>

/**
 * \brief a function to get all the filenames in the directory
 * \param directory the directory 
 * \return the filenames in the directory
 */
std::vector<std::string> filesInDir(const std::string &directory)
{
    std::vector<std::string> files;
    for (const auto &elem : std::filesystem::directory_iterator(directory))
        if (elem.status().type() != std::filesystem::file_type::directory)
            files.push_back(std::filesystem::canonical(elem.path()).c_str());
    std::sort(files.begin(), files.end());
    return files;
}

int main(int argc, char const *argv[])
{
    auto fs = filesInDir("../src");
    for (const auto &filename : fs)
        std::cout << filename << std::endl;
    return 0;
}
