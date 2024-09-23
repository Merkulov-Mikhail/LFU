#include <list>
#include <map>

template <typename TYPE>
struct cache_t {
    private:

        struct el {
            int  lastAcc;
            int totalAcc;
        };

        std::map<TYPE, el> cacheMap;

        int capacity     = 100;
        int accessCount = 0;
    public:
        cache_t(int cap) {
            if (cap > 0)
                capacity = cap;
        }

    public:
        cache_t() {}

    public:
        // if elem was found in cache, then returns true
        // if elem was not found in cache than returns false
        bool touchElem(TYPE elem) {
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
        void addElem(TYPE elem) {
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
