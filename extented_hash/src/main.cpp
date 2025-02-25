#include <iostream>
#include "include/extendiblehash.h"
using namespace std;


int main(){
    cout<<"hello world"<<endl;
    // 创建一个桶容量为 2 的可扩展哈希表
    ExtendibleHash hashTable(2);

    // 插入一系列键值对
    int keys[]   = {5, 15, 25, 35, 45, 55};
    int values[] = {50, 150, 250, 350, 450, 550};
    for (int i = 0; i < 6; ++i) {
        cout << "Inserting (" << keys[i] << ", " << values[i] << ") ..." << endl;
        cout<<"开始插入"<<endl;
        hashTable.insert(keys[i], values[i]);
        cout<<"结束插入"<<endl;
        hashTable.print();
        cout << "---------------------------" << endl;
    }
    // 查找一些键对应的值
    try {
        cout << "Find key 25: " << hashTable.find(25) << endl;
        cout << "Find key 55: " << hashTable.find(55) << endl;
        cout << "Find key 100: " << hashTable.find(100) << endl;
    } catch (const runtime_error &e) {
        cout << e.what() << endl;
    }
    return 0;
}