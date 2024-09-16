#include <iostream>
#include "cache.h"

int main(int argc, const char* argv[]) {
    // elems size
    int nElems = 0;
    int cacheSize = 0;
    int ans = 0;
    std::cin >> cacheSize >> nElems;

    cache_t<int>Cache(cacheSize);

    int current = 0;
    for ( ; nElems; nElems-- ) {
        std::cin >> current;
        if (Cache.touchElem(current)) {
            ans += 1;
        }
        else {
            Cache.addElem(current);
        }
    }

    std::cout << ans << std::endl;

}
