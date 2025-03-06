// LRU算法的实现
#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;
class LRUCache
{
public:
    LRUCache(int capacity): m_capacity(capacity){}
    virtual ~LRUCache(){}
    int get(int key) {
        if(m_hashTable.find(key) == m_hashTable.end()) {
            return -1;
        }
        auto& iter = m_hashTable[key];
        m_items.splice(m_items.begin(), m_items, iter);
        return iter->second;
    }

    void set(int key, int value) {
        if(m_hashTable.find(key) != m_hashTable.end()) {
            auto& iter = m_hashTable[key];
            iter->second = value;
            m_items.splice(m_items.begin(), m_items, iter);
            return ;
        }
        if(m_items.size() >= m_capacity){
            auto& back = m_items.back();
            m_items.pop_back();
            m_hashTable.erase(back.first);  // 删除最后一个元素
        }   

        m_items.push_front({key, value});
        m_hashTable[key] = m_items.begin();                                                     

    }

    void printLRU() {
        for(auto item: m_items) {
            cout<<item.first<<" "<<item.second<<endl;
        }
    }


private:
   list<pair<int, int>> m_items;
   size_t m_capacity;
   unordered_map<int, list<pair<int, int>>::iterator> m_hashTable; 
};

int main() {
    LRUCache lru(3);
    lru.set(1, 11);
    lru.set(2, 12);
    lru.set(3, 13);
    lru.set(4, 14);
    lru.set(1, 15);
    lru.printLRU();

    return 0;
}