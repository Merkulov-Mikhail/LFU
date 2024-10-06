#include <cstdlib>
#include <iostream>
#include "cache.h"

int main(int argc, const char* argv[]) {
    // elems size
    int nElems = 0;
    int cacheSize = 0;
    int ans = 0;
    std::cin >> cacheSize >> nElems;
    std::vector<int> items;
    caches::lfu_t<int>Cache(cacheSize);

    int current = 0;
    for ( ; nElems; nElems-- ) {
        std::cin >> current;
        items.push_back(current);
        if (Cache.touchElem(current)) {
            ans += 1;
        }
        else {
            Cache.addElem(current);
        }
    }

    std::cout << "Perfect cache:\t" << caches::idealCache(cacheSize, items) << std::endl;
    std::cout << "LFU Cache:\t" << ans << std::endl;



    // Comparison between ideal and LFU caches
    // 2000 elements ranging from 0 to 200, cache size - 100
    items.clear();
    for (int i = 0; i < 2000; i++)
        items.push_back(rand() % 200);

    caches::lfu_t<int>anotherCacheTry(100);
    ans = 0;

    for (nElems = 0 ; nElems < 2000; nElems++ ) {
        if (anotherCacheTry.touchElem(items[nElems]))
            ans += 1;
        else
            anotherCacheTry.addElem(items[nElems]);
    }
    std::cout << "Perfect cache:\t" << caches::idealCache(100, items) << std::endl;
    std::cout << "LFU Cache:\t" << ans << std::endl;

}
