#include <iostream>
#include <vector>

/**
 * @brief find the value that there are k values less than it in the value container
 * 
 * @tparam _Container the type of the value container
 * @param vals the value container
 * @return _Container::value_type the type of return value
 */
template <typename _Container>
typename _Container::value_type findKMins(const _Container &vals, std::size_t k)
{
    using value_type = typename _Container::value_type;
    if (vals.size() == 0)
        return value_type();
    else if (vals.size() == 1)
        return vals.front();
    else
    {
        value_type a = vals.at(vals.size() / 2);
        _Container s1, s2, s3;
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
 * @tparam _Container the type of the value container
 * @param vals the value container
 * @return _Container::value_type the type of return value
 */
template <typename _Container>
typename _Container::value_type findMedia(const _Container &vals)
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
