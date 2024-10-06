#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include "cache.h"

int fileTest(const char* fileName);
void basicTests();


void success(const char* string);
void error(const char* string);



int main(int argc, const char* argv[]) {
    if (argc != 1) {
        int all = 0;
        int pos = 1;
        if (!strcmp(argv[1], "--all") || !strcmp(argv[1], "-a")) {
            all = 1;
            pos = 2;
        }
        int err;
        // assumes, that everything in argv is files, that contain tests
        for ( int i = pos; i < argc; i++ ) {
            printf("TEST #%d(%s)\n", i - pos, argv[i]);
            // if we do not stop on error and a test fails, then end testing
            if (fileTest(argv[i])) {
                error("FAILED\n");
                if (!all)
                    return 0;
            }
            else {
                success("PASSED\n");
            }
        }

        return 0;
    }
    basicTests();
    return 0;
}

void basicTests() {

    caches::lfu_t<int>cache(3);

    assert(cache.touchElem(50) == false);
    cache.addElem(49);
    assert(cache.touchElem(50) == false);
    assert(cache.touchElem(49) == true);

    cache.addElem(48);
    cache.addElem(47);

    assert(cache.touchElem(49) == true);

    // 47 in in cache, so touchElem must do nothing
    assert(cache.touchElem(47) == true);
    assert(cache.touchElem(48) == true);
    assert(cache.touchElem(47) == true);
    assert(cache.touchElem(48) == true);
    // 3 touches to 47, 48, 49
    // adding new element will force the 49 get deleted (cause it's the oldest element)
    cache.addElem(50);

    assert(cache.touchElem(49) == false);

    cache.touchElem(50);
    cache.touchElem(50);
    cache.touchElem(50);
    cache.touchElem(48);
    cache.addElem(51);
    assert(cache.touchElem(51) == true);
    assert(cache.touchElem(50) == true);
    assert(cache.touchElem(48) == true);
    assert(cache.touchElem(47) == false);

    printf("\"Does this work?\"");
    success(" PASSED\n");

}

int fileTest(const char* fileName) {
    std::ifstream in(fileName);
    std::streambuf* prev = std::cin.rdbuf(in.rdbuf());

    int nElems = 0;
    int cacheSize = 0;
    int ans = 0;
    std::cin >> cacheSize >> nElems;

    caches::lfu_t<int>Cache(cacheSize);

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
    int correct;
    std::cin >> correct;
    printf("RESULT:   %d\nAWAITING: %d\n", ans, correct);
    std::cin.rdbuf(prev);

    return correct != ans;
}

void error(const char* string) {
    printf("\033[31m%s\033[0m", string);
}

void success(const char* string) {
    printf("\033[32m%s\033[0m", string);
}
