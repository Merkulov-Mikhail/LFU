#include <list>
#include <map>
#include <vector>
#include <set>

namespace caches {
    template <typename TYPE>
    struct lfu_t {
        private:

            struct el {
                int  lastAcc;
                int totalAcc;
            };

            std::map<TYPE, el> cacheMap;

            int capacity     = 100;
            int accessCount = 0;
        public:
            lfu_t(int cap) {
                if (cap > 0)
                    capacity = cap;
            }

        public:
            lfu_t() {}

        public:
            // if elem was found in cache, then returns true
            // if elem was not found in cache than returns false
            bool touchElem(const TYPE elem) {
                if (cacheMap.count(elem)) {
                    accessCount++;
                    cacheMap[elem].totalAcc += 1;
                    cacheMap[elem].lastAcc  = accessCount;
                    return true;
                }
                return false;
            }

        public:
            // add an element into cache
            // delete extra elements if needed
            void addElem(const TYPE elem) {
                if (touchElem(elem)) {
                    return;
                }

                while (cacheMap.size() >= capacity) {
                    TYPE deleteElem;
                    int minDeleteVal = INT_MAX;
                    int lastAccess   = INT_MAX;
                    for (auto it = cacheMap.begin(); it != cacheMap.end(); it++) {
                        if ((minDeleteVal > it->second.totalAcc) ||
                            (minDeleteVal == it->second.totalAcc && lastAccess > it->second.lastAcc)) {
                            deleteElem = it->first;
                            minDeleteVal = it->second.totalAcc;
                            lastAccess = it->second.lastAcc;
                        }
                    }
                    cacheMap.erase(deleteElem);
                }
                accessCount++;
                cacheMap[elem].totalAcc = 1;
                cacheMap[elem].lastAcc  = accessCount;

            }

    };


    template <typename TYPE>
    int idealCache(int size, const std::vector<TYPE> elems) {

        int pos = 0;
        int ans = 0;

        std::set<TYPE> cache;
        while (cache.size() < size && pos < elems.size()) {
            if (cache.find(elems[pos]) != cache.end())
                ans++;
            else
                cache.insert(elems[pos]);

            pos++;
        }


        std::map<TYPE, int> lastElemsMap;
        TYPE lastElem;

        for (; pos < elems.size(); pos++) {
            if (cache.find(elems[pos]) != cache.end()) {
                ans++;
            }
            else {
                lastElemsMap.clear();
                for (int i = pos; i < elems.size(); i++) {
                    if (cache.find(elems[i]) != cache.end() && lastElemsMap.count(elems[i]) == 0) {
                        lastElemsMap[elems[i]] = 1;
                        lastElem = elems[i];
                    }
                }

                // if there are elems in cache, that will not be present in the future, we can delete any of them
                if (lastElemsMap.size() < cache.size()) {
                    for ( auto i = cache.begin(); i != cache.end(); i++ ) {
                        if (lastElemsMap.count(*i) == 0) {
                            lastElem = *i;
                            break;
                        }
                    }
                }
                cache.erase(lastElem);
                cache.insert(elems[pos]);
            }
        }

        return ans;
    }
}
