#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
// 实现string类需要实现的接口：
// 1. 构造函数
// 2. 析构函数
// 3. 拷贝构造函数
// 4. 移动构造函数
//////////////////////////////////////

// 5. 赋值运算符
// 6. 移动赋值运算符
// 7. 实现append函数
//////////////////////////////////////
//  细节：
// 构造函数，初始化为0长度字符串，支持C风格字符串
// 可以考察的点：SSO优化、深拷贝与移动语义的区别、扩容策略选择等实现细节

class MyString{
private:
    // 小对象优化(SSO)缓冲区大小
    static const size_t LOCAL_BUF_SIZE = 15;
    union {
        char localBuf[LOCAL_BUF_SIZE + 1];
        struct {
            char* heapPtr;     // 堆内存指针
            size_t capacity;    // 分配的内存容量
        } ;
    };
    size_t length;              // 当前字符串长度
    bool isLocal;               // 是否使用本地缓存
    // 重新分配内存(参考STL的m_create实现)
    void reallocate(size_t newCapacity) {
        if(newCapacity <= capacity && !isLocal) {
            return;
        }
        char* newPtr = new char[newCapacity + 1]; // 在堆上分配新的空间
        memcpy(newPtr, data(), length);
        newPtr[newCapacity] = '\0';
        if(!isLocal) {
            delete[] heapPtr;       // 如果以前已经是在堆上分配的内存，那么显示放掉
        } else {
            isLocal = false;
        }
        heapPtr = newPtr;
        capacity = newCapacity;

    }

public:
    // 构造函数(参考STL basic_string的构造实现)
    MyString(): length(0), isLocal(true) {
        localBuf[0] = '\0';
    } 
    MyString(const char* str): MyString() {
        size_t strLen = strlen(str);
        if(strLen > LOCAL_BUF_SIZE) {
            isLocal = false;
            capacity = max(strLen, LOCAL_BUF_SIZE * 2); // 注意此时的容量并不是直接和传入的字符串常量一样
            heapPtr = new char[capacity + 1];
            memcpy(heapPtr, str, strLen + 1);   // target, source, length
        } else {
            memcpy(localBuf, str, strLen + 1);
        }

        length = strLen;
    }

    // 拷贝控制
    MyString(const MyString& other): MyString() {
        *this = other;
    }
    // 赋值运算符
    MyString& operator=(const MyString& other) {
        if(this != &other) {
            clear();
            if(other.isLocal) {
                memcpy(localBuf, other.localBuf, length = 1);
                isLocal = true;
            } else {
                reallocate(other.capacity);
                memcpy(heapPtr, other.heapPtr, other.length + 1);
            }
            length = other.length;
        }
        return *this;
    }
    // 移动语义
    MyString(MyString&& other) noexcept {
        if(other.isLocal) {
            memcpy(localBuf, other.localBuf, other.length + 1);
            isLocal = true;
        } else {    
            heapPtr = other.heapPtr;
            capacity = other.capacity;
            isLocal = false;
        }
        length = other.length;
        other.length = 0;
        other.localBuf[0] = '\0';
    }
    // 析构函数
    ~MyString() {
        if(!isLocal) {  
            delete[] heapPtr;
        }
    }

    // 访问数据(兼容STL接口)
    const char* c_str() const noexcept{
        return isLocal ? localBuf : heapPtr;
    }
    size_t size() const noexcept {return length;}
    // 元素访问
    char& operator[](size_t pos) {
        if(pos > length) {
            throw out_of_range("MyString index out of range");
        }
        return isLocal ? localBuf[pos] : heapPtr[pos];
    }
    // 容量管理(参考STL reverse实现)
    void reserve(size_t newCapacity) {
        if(newCapacity > this->capacity || isLocal) {
            reallocate(max(newCapacity, length + 1));
        }
    } 

    // 修改操作(实现COW优化)
    MyString& append(const char* str, size_t count) {
        size_t newLength = length + count;
        if(newLength > capacity) {
            reserve(max(newLength, capacity * 2));
        }
        memcpy(data() + length, str, count);
        length = newLength;
        data() [length] = '\0';
        return *this;
    }

    void clear() noexcept{
        if(!isLocal) {
            delete[] heapPtr;
            isLocal = true;
        }
        localBuf[0] = '\0';
        length = 0;
    }

private:
    char* data() {
        return isLocal ? localBuf : heapPtr;
    }

    const char* data() const {
        return isLocal ? localBuf : heapPtr;
    }
};

// 运算符重载
MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString result(lhs);
    result.append(rhs.c_str(), rhs.size());
    return result;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}


int main() {
    MyString s1;                     // 空字符串（使用本地缓冲区）
    MyString s2 = "Hello";           // 短字符串（SSO优化）
    MyString s3 = "This is a very long string that exceeds local buffer size";
    
    MyString s4 = s2;                // 拷贝构造
    MyString s5 = std::move(s3);     // 移动构造
    
    s4.append(" World!", 6);         // 追加操作
    if (s4 == "Hello World") {       // 比较操作
        // ...
    }
    return 0;
}


