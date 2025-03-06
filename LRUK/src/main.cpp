#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <stdexcept>

using namespace std;
struct Node{
    int key_;
    int value_;
    Node(){}
    Node(int key, int value): key_(key), value_(value){}

};

class LRUK{
public:
    LRUK(size_t capacity, int k): capacity_(capacity), k_(k){}
    // 获取缓存项
    Node get(int key) {
        auto iter = cache_.find(key);
        if(iter == cache_.end()) {
            throw runtime_error("Key not found");
        }
        recordAccess(iter->second);  //
        return iter->second.cacheData_;
    }
    // 插入或更新缓存项
    void put(int key, int value) {
        auto iter = cache_.find(key);
        if(iter != cache_.end()) {
            iter->second.cacheData_.value_ = value;
            recordAccess(iter->second);  // 跟新一个次访问时间
        } else{
            if(cache_.size() >= capacity_) {
                evict();
            }
            CacheEntry entry;
            entry.cacheData_.value_= value;
            entry.cacheData_.key_ = key;
            entry.accessTimes_.push_back(++timestamp_);
            cache_[key] = entry;
        }
    }


private:
    struct CacheEntry{
        Node cacheData_;
        vector<long long> accessTimes_;
    };
    unordered_map<int, CacheEntry> cache_;  // 只需要使用哈希表来存储数据项
    size_t capacity_;
    int k_;
    long long timestamp_;
    // 记录一次访问，将当前时间戳插入到访问记录中
    void recordAccess(CacheEntry& entry) {
        entry.accessTimes_.push_back(++timestamp_);
    }

    // 淘汰算法，遍历所有缓存项，找到第K次最近访问时间最早的项进行淘汰
    void evict() {
        int candidate;
        bool found = false;
        long long minKthTime = __LONG_LONG_MAX__;
        for(auto& item: cache_) {
            const auto  entry = item.second;
            long long kthTime;
            if(entry.accessTimes_.size() < k_) {
                kthTime = 0;
            } else {
                kthTime = entry.accessTimes_[entry.accessTimes_.size() - k_];
            }
            if(kthTime < minKthTime) {
                minKthTime = kthTime;
                candidate = entry.cacheData_.key_;
                found = true;
            }
        }
        if(found) {
            cout<<"Evict key: "<<candidate<<endl;
            cache_.erase(candidate);
        }
    }


};
int main() {
    // 创建一个容量为 3，使用 LRU-2 算法的缓存
    LRUK cache(3, 2);

    // 插入一些数据
    cache.put(1, "A");
    cache.put(2, "B");
    cache.put(3, "C");

    // 对 key=1 进行访问（记录第二次访问时间）
    cout << "Get 1: " << cache.get(1) << endl;

    // 插入新数据，触发淘汰
    cache.put(4, "D");

    // 尝试访问 key=2
    try {
        cout << "Get 2: " << cache.get(2) << endl;
    } catch(exception& e) {
        cout << "Key 2 not found" << endl;
    }
    cout << "Get 3: " << cache.get(3) << endl;
    cout << "Get 4: " << cache.get(4) << endl;

    return 0;
}


