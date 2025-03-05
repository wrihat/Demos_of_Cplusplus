#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>
using namespace std;
class SingletonEager{  // 饿汉模式---在程序启动时初始化实例，线程安全但可能影响启动速度
private:
    static SingletonEager instance_;                            // 静态实例变量，保证全局只有一个资源
    SingletonEager(){};                                         // 私有化构造函数，保证不能从外部创建
    SingletonEager(const SingletonEager&) = delete;             // 禁用拷贝构造函数
    SingletonEager& operator=(const SingletonEager&) = delete;  // 禁用赋值
    
    
public:
    static SingletonEager& getInstance() {
        return instance_;
    }
    void log(const std::string& msg) {
        std::cout << "[Eager] " << msg << std::endl;
    }
};
// 静态成员初始化(程序启动时初始完成)
SingletonEager SingletonEager::instance_;

class SingletonLazy{  // 懒汉模式（线程安全版本）---第一次调用时初始化，需加锁保证线程安全。
private:
    static SingletonLazy* instance_;            // 静态实例变量-保证全局唯一资源，使用指针操作，方便初始化
    static std::mutex mtx_;                     // 互斥锁
    SingletonLazy(){};                          // 私有化构造函数
    SingletonLazy(const SingletonLazy&) = delete;   //   复制构造函数
    SingletonLazy& operator=(const SingletonLazy&) = delete;    // 禁用赋值构造函数

public:
    static SingletonLazy* getInstance() {
        std::lock_guard<std::mutex> lock(mtx_);  // 加锁
        if(!instance_) {
            instance_ = new SingletonLazy();
        }
        return instance_;
    }
    void log(const std::string& msg) {
        std::cout << "[Lazy] " << msg << std::endl;
    }


};
// 静态成员初始化
SingletonLazy* SingletonLazy::instance_ = nullptr;  // 初始化的时候为nullptr, 这样保证等到调用getInstance的时候再分配空间、初始化
std::mutex SingletonLazy::mtx_;                     // 初始化互斥锁



class SingletonDCLP{ // 双重锁定检查(线程安全版本)---对懒汉模式多一次检查来优化性能
private:               // 
    static SingletonDCLP* instance_;    // 静态私有化实例变量，保证全局唯一资源
    static std::mutex mtx_;             // 互斥变量-互斥锁，保证线程安全访问
    SingletonDCLP(){};                  // 私有化构造函数-避免外部创建
    SingletonDCLP(const SingletonDCLP&) = delete;   // 禁用复制构造
    SingletonDCLP& operator=(const SingletonDCLP&) = delete;    // 禁用赋值运算符
public:
    static SingletonDCLP* getInstance() {
        // 第一次检查(无锁)
        if(instance_ == nullptr) {
            std::lock_guard<std::mutex> lock(mtx_);
            if(instance_ == nullptr) {
                instance_ = new SingletonDCLP();
            }
        }
        return instance_;
    }
    void log(const std::string& msg) {
        std::cout << "[DCLP] " << msg << std::endl;
    }
};
SingletonDCLP* SingletonDCLP::instance_ = nullptr;
std::mutex SingletonDCLP::mtx_;



#include <thread>
#include <vector>

// 测试函数（多线程访问单例）
void testSingleton(SingletonDCLP* singleton) {
    singleton->log("Thread accessing singleton");
}

int main() {
    // 测试饿汉模式
    SingletonEager& eager1 = SingletonEager::getInstance();
    SingletonEager& eager2 = SingletonEager::getInstance();
    eager1.log("Address: " + std::to_string(reinterpret_cast<uintptr_t>(&eager1)));
    eager2.log("Address: " + std::to_string(reinterpret_cast<uintptr_t>(&eager2)));

    // 测试懒汉模式
    SingletonLazy* lazy1 = SingletonLazy::getInstance();
    SingletonLazy* lazy2 = SingletonLazy::getInstance();
    lazy1->log("Address: " + std::to_string(reinterpret_cast<uintptr_t>(lazy1)));
    lazy2->log("Address: " + std::to_string(reinterpret_cast<uintptr_t>(lazy2)));

    // 测试双重检查锁定（多线程）
    SingletonDCLP* dclp = SingletonDCLP::getInstance();
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(testSingleton, dclp);
    }
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}


