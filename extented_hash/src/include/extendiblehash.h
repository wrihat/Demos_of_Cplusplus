#ifndef _EXTENDIBLEHASH_H_
#define _EXTENDIBLEHASH_H_

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
struct Record{  // 记录结构，保存键值(数据项)
    int key;
    int value;
    Record(int key, int value): key(key), value(value){}
};

struct Bucket{  // 桶结构体，保存局部深度和存储的记录
    int localDepth;
    vector<Record> records;
    Bucket(int depth): localDepth(depth){}
};

class ExtendibleHash{
public:
    ExtendibleHash(int bucketSize); // 构造函数
    virtual ~ExtendibleHash();  // 析构函数
    // 插入或更新键值对
    void insert(int key, int value);
    // 查找键对应的值，不存在则抛出异常
    int find(int key);
    void print();  // 打印桶信息和里面的记录信息

private:
    int bucketSize;             // 每个桶的最大容量
    int globalDepth;            // 目录的全局深度
    vector<Bucket*> directory;  // 目录，存储桶指针
    
    // 简单哈希函数，直接返回key
    inline int hashFunction(int key) {return key;}
    // 根据传入的哈希值以及全局深度来获取目录索引    // 二进制与操作，使得获得的哈希值只关注低globalDepth位(二进制位)
    int getDirectoryIndex(int hashVal);
    // 当桶满时进行桶分裂
    void splitBucket(int directoryIndex);  // 传入目录索引信息来进行桶分裂
    // 扩展目录，将全局深度加1，目录索引数量翻倍
    void doubleDirectory();
};










#endif



