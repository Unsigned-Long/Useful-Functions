#include <iostream>
#include <string>

/**
 * \brief a function to output info to the std::ostream
 * \param str the target string
 * \param ceil whether output the ceil line or not
 * \param floor whether output the floor line or not
 * \param symbol the char type to construct the lin
 * \param os the output stream type
 */
void outputFormat(const std::string &str, bool ceil = false, bool floor = true,
                  char symbol = '-', std::ostream &os = std::cout)
{
    if (ceil)
        os << std::string(str.length(), symbol) << std::endl;
    os << str << std::endl;
    if (floor)
        os << std::string(str.length(), symbol) << std::endl;
    return;
}

int main(int argc, char const *argv[])
{
    outputFormat("Hello, world!", true, true);
    outputFormat("Hey, man!", false, true, '+');
    return 0;
}
