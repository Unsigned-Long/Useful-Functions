#include <iostream>
#include <string>
#include <fstream>

/**
 * \brief a function to read all chars in the file and return a string
 * \param file the opened oouput file stream reference
 * \return the char string in the file
 */
std::string readString(std::ifstream &file)
{
    if (!file.is_open())
        throw std::runtime_error("file open failed in 'std::string readString(std::fstream &file)'");
    file.seekg(0, std::ios::end);
    auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string str(size, ' ');
    file.read(const_cast<char *>(str.c_str()), size);
    return str;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("../.vscode/c_cpp_properties.json", std::ios::in);
    std::cout << readString(file) << std::endl;
    file.close();
    return 0;
}
