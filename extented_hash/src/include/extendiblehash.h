#ifndef _EXTENDIBLEHASH_H_
#define _EXTENDIBLEHASH_H_
#include "hash_table.h"
#include <functional>
#include <mutex>
#include <memory>
#include <list>
namespace bustub{


template<typename K, typename V>
class ExtendibleHashTable: public HashTable<K, V> {
public:
  /**
   *
   * TODO(P1): Add implementation
   *
   * @brief Create a new ExtendibleHashTable.
   * @param bucket_size: fixed size for each bucket
   */
  explicit ExtendibleHashTable(size_t bucket_size);

  /**
   * @brief Get the global depth of the directory.
   * @return The global depth of the directory.
   */
  auto GetGlobalDepth() const -> int;

  /**
   * @brief Get the local depth of the bucket that the given directory index points to.
   * @param dir_index The index in the directory.
   * @return The local depth of the bucket.
   */
  auto GetLocalDepth(int dir_index) const -> int;

  /**
   * @brief Get the number of buckets in the directory.
   * @return The number of buckets in the directory.
   */
  auto GetNumBuckets() const -> int;

  /**
   *
   * TODO(P1): Add implementation
   *
   * @brief Find the value associated with the given key.
   *
   * Use IndexOf(key) to find the directory index the key hashes to.
   *
   * @param key The key to be searched.
   * @param[out] value The value associated with the key.
   * @return True if the key is found, false otherwise.
   */
  auto Find(const K &key, V &value) -> bool override;

  /**
   *
   * TODO(P1): Add implementation
   *
   * @brief Insert the given key-value pair into the hash table.
   * If a key already exists, the value should be updated.
   * If the bucket is full and can't be inserted, do the following steps before retrying:
   *    1. If the local depth of the bucket is equal to the global depth,
   *        increment the global depth and double the size of the directory.
   *    2. Increment the local depth of the bucket.
   *    3. Split the bucket and redistribute directory pointers & the kv pairs in the bucket.
   *
   * @param key The key to be inserted.
   * @param value The value to be inserted.
   */
  void Insert(const K &key, const V &value) override;

  /**
   *
   * TODO(P1): Add implementation
   *
   * @brief Given the key, remove the corresponding key-value pair in the hash table.
   * Shrink & Combination is not required for this project
   * @param key The key to be deleted.
   * @return True if the key exists, false otherwise.
   */
  auto Remove(const K &key) -> bool override;

  /**
   * Bucket class for each hash table bucket that the directory points to.
   */

    class Bucket{
        public:
            explicit Bucket(size_t size, int depth = 0);
        
            /** @brief Check if a bucket is full. */
            inline auto IsFull() const -> bool { return list_.size() == size_; }
        
            /** @brief Get the local depth of the bucket. */
            inline auto GetDepth() const -> int { return depth_; }
        
            /** @brief Increment the local depth of a bucket. */
            inline void IncrementDepth() { depth_++; }
        
            inline auto GetItems() -> std::list<std::pair<K, V>> & { return list_; }
        
            /**
             *
             * TODO(P1): Add implementation
             *
             * @brief Find the value associated with the given key in the bucket.
             * @param key The key to be searched.
             * @param[out] value The value associated with the key.
             * @return True if the key is found, false otherwise.
             */
            auto Find(const K &key, V &value) -> bool;
        
            /**
             *
             * TODO(P1): Add implementation
             *
             * @brief Given the key, remove the corresponding key-value pair in the bucket.
             * @param key The key to be deleted.
             * @return True if the key exists, false otherwise.
             */
            auto Remove(const K &key) -> bool;
        
            /**
             *
             * TODO(P1): Add implementation
             *
             * @brief Insert the given key-value pair into the bucket.
             *      1. If a key already exists, the value should be updated.
             *      2. If the bucket is full, do nothing and return false.
             * @param key The key to be inserted.
             * @param value The value to be inserted.
             * @return True if the key-value pair is inserted, false otherwise.
             */
            auto Insert(const K &key, const V &value) -> bool;
        private:
            size_t size_;
            int depth_;
            std::list<std::pair<K, V>> list_;   // 使用了list(双向链表)来进行存储，而不是vector
    };


private:
    int global_depth_;
    size_t bucket_size_;    // 单个桶中
    int num_buckets_;       // 目录项的个数
    mutable std::mutex latch_;      // 用于并发控制的锁
    std::vector<std::shared_ptr<Bucket>> dir_;
    auto RedistributeBucket(std::shared_ptr<Bucket> bucket) ->void;
    auto IndexOf(const K& key) ->size_t;
    auto GetGlobalDepthInternal() const ->int;
    auto GetLocalDepthInternal(int dir_index) const ->int;
    auto GetNumBucketsInternal() const ->int;
};
template <typename K, typename V>
ExtendibleHashTable<K, V>::ExtendibleHashTable(size_t bucket_size)
{

std::scoped_lock<std::mutex> lock(latch_);
}

template <typename K, typename V>
inline auto ExtendibleHashTable<K, V>::RedistributeBucket(std::shared_ptr<Bucket> bucket) ->void
{


}

template<typename K, typename V>
void ExtendibleHashTable<K, V>::Insert(const K &key, const V &value) {
    std::scoped_lock<std::mutex> lock(latch_);
    while(dir_[IndexOf(key)]->IsFull()) {   // 当桶满了的时候进行分裂
        auto index = IndexOf(key);
        auto target_bucket = dir_[index];
        int mask = 1 << target_bucket->GetDepth();  //  新的两个桶的区分位
        auto bucket_0 = std::make_shared<Bucket>(bucket_size_, target_bucket->GetDepth() + 1);
        auto bucket_1 = std::make_shared<Bucket>(bucket_size_, target_bucket->GetDepth() + 1);
        for(auto& item : target_bucket->GetItems()) {
            size_t hash_key = std::hash<K>()(item.first);
            if((hash_key & mask) != 0U) {
                bucket_1->Insert()
            } else {

            }
        }
    }
    auto index = IndexOf(key);
    auto target_bucket = dir_[index];
    for(auto& item: target_bucket->GetItems()) {   // 插入的时候先查看是否已经存在了对应的数据项
        if(item.first == key) {
            item.seond = value;
            return;
        }
    } 
    target_bucket->Insert(key, value);
}



}

#endif



