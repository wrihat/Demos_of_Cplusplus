#ifndef _COWSTRING_H_
#define _COWSTRING_H_
#include <string>
#include <memory>
#include <cassert>
// 写时复制类，
class COWString{
private:
    //使用智能指针来管理资源
    struct StringData{
        std::string str;            // 实际的字符串内容
        int refCount;                // 共享计数器，表示有多少个对象正在使用这个字符串
        StringData(const std::string& str) : str(str), refCount(1) {}
    };
    std::shared_ptr<StringData> data;   // 智能指针持有字符串数据

    void ensureUnique(){
        // 如果当前对象的数据被其他的对象共享(引用计数大于1)， 则进行复制
        if(data.use_count() > 1) {
            data = std::make_shared<StringData>(data->str);     // 创建副本
        }
    }

public:
    // 构造函数
    COWString(const std::string& s): data(std::make_shared<StringData>(s)) {}

    // 拷贝构造函数
    COWString(const COWString& other) :data(other.data){}
    //赋值运算
    COWString& operator =(const COWString& other) {
        if(this != &other) {
            data = other.data;  // 共享数据
        }
        return* this;
    }

};

#endif // !_COWSTRING_H_
