#include <iostream>
#include <shared_mutex>
#include <vector>
#include <unordered_map>
#include <list>
#include <mutex>
#include <cassert>
using namespace std;
struct Node{
    int key;
    int value;
    Node(int k, int v): key(k), value(v){}
};

class ThreadSafeLRU{
public:
    
    explicit ThreadSafeLRU(size_t capacity): capacity_(capacity){}
    int get(int key) {
        std::shared_lock<mutex> lock(mtx_);
        if(cacheMap_.find(key) == cacheMap_.end()) {
            return -1;
        } 
        auto iter = cacheMap_[key];
        cacheList_.splice(cacheList_.begin(), cacheList_, iter);
        return iter->value;
    }

    void put(int key, int value) {
        std::lock_guard<mutex> lock(mtx_);
        auto iter = cacheMap_.find(key);
        if(iter != nullptr) {
            // 键已经存在了，更新value并移动到头部
            iter->second->value = value;
            cacheList_.splice(cacheList_.begin(), cacheList_, iter->second);
            return ;
        }
        // 如果键不存在，那么插入新节点
        if(cacheList_.size() >= capacity_) {  // 弹出最后一个数据项
            auto& evictCache = cacheList_.back();
            cacheMap_.erase(evictCache.value);
            cacheList_.pop_back();
        }
        // 插入新节点
        cacheList_.push_front(Node(key, value));
        cacheMap_[key] = cacheList_.begin();
    }
private:
    size_t capacity_;
    list<Node> cacheList_;
    unordered_map<int, list<Node>::iterator> cacheMap_;
    mutex mtx_;
};

int main() {





    return 0;
}


