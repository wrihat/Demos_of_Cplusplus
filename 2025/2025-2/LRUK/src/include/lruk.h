#ifndef  _LRUK_H_
#define _LRUK_H_
#include <iostream>
#include <unordered_map>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <vector>

template<typename Key, typename Value>
class LRU_Cache
{
public:
    // 构造函数
    LRU_Cache(size_t capacity, int k) : capacity_(capacity), k_(k), timestamp_(0){}
    // 获取缓存项
    Value get(const Key& key) {
        auto iter = cache_.find(key);
        if(iter == cache_.end()) {
            throw std::runtime_error("Key not found");
        }
        recordAccess(iter->second);
        return iter->second.value;
    }

    // 插入缓存项
    void put(const Key& key, const Value& value) {
        auto iter = cache_.find(key);
        if(iter != cache_.end()) {
            iter->second.value = value;
            recordAccess(iter->second);
            return;
        }
        // 如果缓存已满，则进行淘汰 
        if(cache_.size() > capacity_) {
            evict();
        }
        // 添加一个新的缓存项
        CacheEntry entry;
        entry.value = value;
        entry.accessTimes.push_back(++timestamp_);
        cache_[key] = entry;
    }


private:
    struct CacheEntry{   //  缓存项实体： value + 访问时间戳数组
        Value value;
        std::vector<long long> accessTimes;
    };
    std::unordered_map<Key, CacheEntry> cache_;
    size_t capacity_;       // 容量
    int k_;                 // k值
    long long timestamp_;   // 时间戳   线性增长
    
    // 记录一次访问，将当前时间戳插入到访问记录中
    void recordAccess(CacheEntry& entry) {
        entry.accessTimes.push_back(++timestamp_);
    }
    // 淘汰算法： 遍历所有缓存项，找到第k次最近访问时间最早的项进行淘汰
    void evict() {
        Key candidate;
        bool found = false;
        long long minKthTime = std::numeric_limits<long long>::max();
        // 遍历缓存中的每一项
        for(const auto& kv: cache_) {
            const CacheEntry& entry = kv.second;
            long long kthTime;
            // 如果访问次数少于k次则直接赋值为0
            if(entry.accessTimes.size() < static_cast<size_t>(k_)) {
                kthTime = 0;
            } else {
                // 使用第k次最近的访问时间
                kthTime = entry.accessTimes[entry.accessTimes.size() - k_];   // 访问的时间戳记录数组会随着访问的次数增多而持续增长，
            }
            if(kthTime < minKthTime) {
                minKthTime = kthTime;
                candidate = kv.first;
                found = true;
            }
        }
        if(found) {
            std::cout<<"Evicting key: "<<candidate<<std::endl;
            cache_.erase(candidate);  // 删除对应的缓存项
        }
    }

};


#endif // ! _LRUK_H_

