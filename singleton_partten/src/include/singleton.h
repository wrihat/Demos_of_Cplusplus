#ifndef _SINGLETON_H_
#define _SINGLETON_H_
class Singleton{
public:
    static Singleton& getInstance() {
        
    }

private:
    static Singleton* instance_;
    Singleton(){};                              // 私有化构造函数--》避免外部构造
    Singleton(const Singleton& ) = delete;      // 禁止使用拷贝构造
    Singleton& operator=(const Singleton&) = delete; // 禁用赋值运算符
};



#endif // !_SINGLETON_H_
