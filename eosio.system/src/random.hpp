#include <cstdlib>
#include <algorithm>
namespace Random
{
    #include "mersenne-twister.hpp"

    /**
     * shuffle iterator 
     * See https://en.cppreference.com/w/cpp/algorithm/random_shuffle
     */
    template <class RandomIt>
    void shuffle(RandomIt first, RandomIt last)
    {
        typename std::iterator_traits<RandomIt>::difference_type i, n;
        n = last - first;
        for (i = n - 1; i > 0; --i)
        {
            std::swap(first[i], first[rand_u32() % (i + 1)]);
        }
    }
} // namespace Random