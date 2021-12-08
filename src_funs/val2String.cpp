#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

/**
 * @brief Converts a float number to a string with the specified number of reserved digits
 * 
 * @param val the value to be converted
 * @param prec the specified number of reserved digits 
 * @return std::string 
 */
std::string val2String(const float &val, std::size_t prec = 3)
{
    std::stringstream stream;
    stream << std::setiosflags(std::ios::fixed) << std::setprecision(prec) << val;
    return stream.str();
}

int main(int argc, char const *argv[])
{
    std::cout << val2String(3.1415926535) << std::endl;
    return 0;
}
