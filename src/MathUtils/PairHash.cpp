#ifndef PAIRHASH_CPP
#define PAIRHASH_CPP

#include <utility>
#include <algorithm>
#include <vector>

struct PairHash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        auto h1 = std::hash<T1>{}(pair.first);
        auto h2 = std::hash<T2>{}(pair.second);
        return h1 ^ h2;
    }
};

#endif