#include <iostream>
#include <vector>
#include <functional>

/**
 * @brief find the value that there are k values less than it in the value container
 * 
 * @tparam _Ty the type of the element
 * @param vals the value container
 * @param k the parameter
 * @return _Ty the result
 */
template <typename _Ty>
_Ty findKMins(const std::vector<_Ty> &vals, std::size_t k)
{
    if (vals.size() == 0)
        return _Ty();
    else if (vals.size() == 1)
        return vals.front();
    else
    {
        _Ty a = vals.at(vals.size() / 2);
        std::vector<_Ty> s1, s2, s3;
        for (const auto &elem : vals)
            if (elem < a)
                s1.push_back(elem);
            else if (elem > a)
                s3.push_back(elem);
            else
                s2.push_back(elem);
        if (s1.size() >= k)
            return findKMins(s1, k);
        else if (s1.size() + s2.size() >= k)
            return a;
        else
            return findKMins(s3, k - s1.size() - s2.size());
    }
}

/**
 * @brief fing the media value in the value container
 * 
 * @tparam _Ty the type of the element
 * @param vals the value container
 * @return _Ty the result
 */
template <typename _Ty>
_Ty findMedia(const std::vector<_Ty> &vals)
{
    return findKMins(vals, vals.size() / 2);
}

int main(int argc, char const *argv[])
{
    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << findKMins(vals, 3) << std::endl;
    std::cout << findKMins(vals, 4) << std::endl;
    std::cout << findMedia(vals) << std::endl;

    return 0;
}
