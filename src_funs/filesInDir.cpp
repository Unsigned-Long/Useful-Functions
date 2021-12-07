#include <iostream>
#include <vector>
#include <fstream>

/**
 * \brief a function to get all the filenames in the directory
 * \param directory the directory 
 * \return the file names in the directory
 */
std::vector<std::string> filesInDir(const std::string &directory)
{
    std::string command = "ls " + directory + "> ./.files.txt";
    auto re = std::system(command.c_str());
    std::fstream file("./.files.txt", std::ios::in);
    std::string filename;
    std::vector<std::string> filenames;
    while (std::getline(file, filename))
        filenames.push_back(directory + '/' + filename);
    file.close();
    command = "rm ./.files.txt";
    re = std::system(command.c_str());
    return filenames;
}

int main(int argc, char const *argv[])
{
    auto ls = filesInDir("../src_funs");
    for (const auto &file : ls)
        std::cout << file << std::endl;
    return 0;
}
