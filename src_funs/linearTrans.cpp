#include <iostream>
#include <functional>

/**
 * \brief a function to generate a function that maps value from [srcMin, srcMax] to [dstMin, dstMax] linearly
 * \param srcMin the lower boundary of the source value range
 * \param srcMax the upper boundary of the source value range
 * \param dstMin the lower boundary of the target value range
 * \param dstMax the upper boundary of the target value range
 * \return the function to project input value
 */

template <typename _Ty>
auto linearTrans(const _Ty &srcMin, const _Ty &srcMax, const _Ty &dstMin, const _Ty &dstMax)
{
    auto srcRange = srcMax - srcMin;
    auto dstRange = dstMax - dstMin;
    return [srcMin, dstMin, srcRange, dstRange](const _Ty &val) -> _Ty
    {
        return (val - srcMin) / srcRange * dstRange + dstMin;
    };
}

/**
 * \brief a function to map value in the [srcMin, srcMax] to the range of [0.0, 1.0]
 * \param srcMin the lower boundary of the source range
 * \param srcMax the upper boundary of the source range
 * \param val the value in the [srcMin, srcMax] to mapped
 */
auto linearNormalize = [](const double &srcMin, const double &srcMax, const double &val) -> double
{
    return std::bind(std::function<decltype(linearTrans<double>)>(linearTrans<double>),
                     std::placeholders::_1, std::placeholders::_2, 0.0, 1.0)(srcMin, srcMax)(val);
};

int main(int argc, char const *argv[])
{
    std::cout << linearNormalize(0.0, 100.0, 20.0) << std::endl;
    std::cout << linearTrans<double>(10.0, 20.0, 0.0, 1.0)(15.0) << std::endl;
    return 0;
}
