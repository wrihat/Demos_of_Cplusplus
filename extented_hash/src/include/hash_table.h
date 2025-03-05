#pragma
namespace bustub{
template<typename K, typename V>
class HashTable{
public:
    HashTable() = default;
    virtual ~HashTable() = default;
    virtual auto Find(const K &key, V &value) -> bool = 0;
    virtual auto Remove(const K &key) -> bool = 0;
    virtual void Insert(const K &key, const V &value) = 0;
};

}