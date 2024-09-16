#pragma once

#include <list>
#include <map>

template <typename TYPE>
struct cache_t {
    private:
        std::list<TYPE> inQ ;
        std::list<TYPE> outQ;
        std::list<TYPE> hotQ;
        std::map <TYPE, int> inMap;
        std::map <TYPE, int> outMap;
        std::map <TYPE, int> hotMap;

        int inCapacity ;
        int outCapacity;
        int hotCapacity;
    public:
        cache_t(int cap) {
            if (cap < 1) {
                cap = 1;
            }
            switch (cap) {
                case (1):
                    inCapacity  = 1;
                    outCapacity = 0;
                    hotCapacity = 0;
                    break;
                case (2):
                    inCapacity  = 2;
                    outCapacity = 0;
                    hotCapacity = 0;
                    break;
                case (3):
                    inCapacity  = 1;
                    outCapacity = 1;
                    hotCapacity = 1;
                    break;
                default:
                    inCapacity  = cap / 4;
                    outCapacity = cap / 2;
                    hotCapacity = cap - inCapacity - outCapacity;
                    break;
            }
        }

    public:
        cache_t() {
            inCapacity  = 1;
            outCapacity = 2;
            hotCapacity = 1;
        }

    public:
        // if elem was found in cache than returns true
        // if elem was not found in cache than returns false
        bool touchElem(TYPE elem) {
            if (inMap.find(elem) != inMap.end()) {
                return true;
            }
            if (outMap.find(elem) != outMap.end()) {
                outQ.remove(elem);
                outMap.erase(elem);

                hotQ.push_front(elem);
                hotMap[elem] = 1;
                if (hotQ.size() > hotCapacity ) {
                    hotMap.erase(hotQ.back());
                    hotQ.pop_back();
                }
                return true;
            }
            if (hotMap.find(elem) != hotMap.end()) {
                return true;
            }
            return false;
        }

    public:
        // add an element into cache
        void addElem(TYPE elem) {
            inQ.push_front(elem);
            inMap[elem] = 1;

            if (inQ.size() > inCapacity) {
                TYPE tmp = inQ.back();
                inQ.pop_back();
                inMap.erase(tmp);

                outQ.push_front(tmp);
                outMap[tmp] = 1;

                if (outQ.size() > outCapacity) {
                    outMap.erase(outQ.back());
                    outQ.pop_back();
                }
            }
        }

};
