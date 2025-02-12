#include <iostream>
#include <list>
#include <utility>
#include <unordered_map>

class LRUCache {
public:
    int get(int key) {
        if(m_hashTable.find(key) == m_hashTable.end()) return -1;
        auto iter = m_hashTable[key];
        m_items.splice(m_items.begin(), m_items, iter);
        return iter->second;
    }
    
    void put(int key, int value) {
        if(m_hashTable.find(key) != m_hashTable.end()) {
            auto iter = m_hashTable[key];
            iter->second = value;
            m_items.splice(m_items.begin(), m_items, iter);
            return ;
        }
        if(m_items.size() >= m_capacity) {
            auto delKey = m_items.back().second;
            m_hashTable.erase(delKey);
            m_items.pop_back();
        }
        m_items.push_front({key, value});
        m_hashTable[key] = m_items.begin();
    }



private:
    std::list<std::pair<int, int>> m_items;
    size_t m_capacity;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_hashTable;
};




int main() {
    




    return 0;
}

