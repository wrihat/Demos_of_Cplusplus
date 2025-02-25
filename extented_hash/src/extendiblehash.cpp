#include "include/extendiblehash.h"
#include <algorithm>
#include "include/extendiblehash.h"

ExtendibleHash::ExtendibleHash(int bucketSize)
    :bucketSize(bucketSize), globalDepth(1)
{
    int directorySize = (1 << globalDepth) - 1;
    directory.resize(directorySize, nullptr);
    for(int i = 0; i < directorySize; i++) {
        directory[i] = new Bucket(globalDepth);
    }
}

ExtendibleHash::~ExtendibleHash() {
    // 目录中可能存在多个相同的桶指针，只释放唯一的桶
    vector<Bucket*> uniqueBuckets;
    for(auto bucketPtr: directory) {
        if(std::find(uniqueBuckets.begin(), uniqueBuckets.end(), bucketPtr) == uniqueBuckets.end()) {
            uniqueBuckets.push_back(bucketPtr);
        }
    }
    for(auto bucketPtr: uniqueBuckets) {
        delete bucketPtr;
    }
}

void ExtendibleHash::insert(int key, int value) {
    int hashVal = hashFunction(key);
    cout<<"计算得到的hash值："<<hashVal<<endl;
    int index = getDirectoryIndex(hashVal);
    cout<<"获取Bucket指针"<<endl;
    Bucket* bucket = directory[index];
    cout<<"获取Bucket指针成功"<<endl;
    // 若键已存在，则更新值
    for (auto &record : bucket->records) {
        cout<<"当前的key值："<<record.key<<endl;
        if (record.key == key) {
            record.value = value;
            return;
        }
    }

    // 如果桶未满，则直接插入新记录
    if (bucket->records.size() < bucketSize) {
        cout<<"桶未满, 直接插入"<<endl;
        bucket->records.push_back(Record(key, value));
    } else {
        // 桶满时，先进行桶分裂，再重新插入该记录
        splitBucket(index);
        insert(key, value);
    }

}

int ExtendibleHash::find(int key)
{
    int hashVal = hashFunction(key);
    int directoryIndex = getDirectoryIndex(hashVal);
    Bucket* bucket = directory[directoryIndex];
    for(auto& record: bucket->records) { // 直接顺序遍历
        if(record.key == key) {
            return record.value;
        }
    }
    throw runtime_error("Key not found");
}

void ExtendibleHash::print() {
    int directorySize = directory.size();
    cout << "Global Depth: " << globalDepth << ", Directory Size: " << directorySize << endl;
    for (int i = 0; i < directorySize; ++i) {
        cout << "Directory[" << i << "]: Bucket@" << directory[i]
             << " (Local Depth: " << directory[i]->localDepth << ") Records: ";
        for (auto &record : directory[i]->records) {
            cout << "{" << record.key << ":" << record.value << "} ";
        }
        cout << endl;
    }
}

int ExtendibleHash::getDirectoryIndex(int hashVal)
{
    int mask = (1<<globalDepth) - 1;
    return hashVal & mask;
}

void ExtendibleHash::splitBucket(int directoryIndex)// 对指定索引的桶进行分裂(因为是在桶满了的情况下才要分裂，所以前提就是已经满容量了)
{   
    Bucket* bucket = directory[directoryIndex];
    int localDepth = bucket->localDepth;
    if(localDepth == globalDepth) {  // 如果局部深度等于全局深度，则先对目录项进行扩展一倍
        doubleDirectory();
    }
    // 新建一个桶，新桶的局部深度为原桶的局部深度加1
    Bucket* newBucket = new Bucket(bucket->localDepth + 1); 
    // 更新原桶的局部深度
    bucket->localDepth++;
    // 根据新增的那一位(分裂位)更新目录指针
    int splitBit = 1 << (bucket->localDepth - 1);  // 最高位，也就是最左边的位，来进行区分
    int dirSize = directory.size();
    for(int i = 0; i < dirSize; i++) {
        if(directory[i] == bucket) {  // 找到了指向旧桶的指针
            if((i & splitBit) != 0) {   // 如果分裂位上为1，则指向新桶
                directory[i] = newBucket;
            }
        }
    }

    // 将原桶中的记录重新分配到两个桶中
    vector<Record> oldRecord = bucket->records;
    bucket->records.clear();    // 先清空原先的数据；
    for(auto& record: oldRecord) {
        int index = getDirectoryIndex(hashFunction(record.key));        // 因为globalDepth可能已经改变了，所以需要重新计算索引值
        directory[index]->records.push_back(record);
    }
    
}

void ExtendibleHash::doubleDirectory()
{
    int oldSize = directory.size();
    globalDepth++;
    directory.resize(1 << globalDepth); // 将原目录的尺寸扩展到2倍的大小
    for(int i = 0; i < oldSize; i++) {
        directory[i + oldSize] = directory[i];      //相当于向后扩展了一倍，然后指针的指向都是跟对应的位置相同
    }

}





