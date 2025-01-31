#include <iostream>
#include <mutex>
using namespace std;
class Singleton{
public:
    static Singleton* getInstance() {
        if(m_instance == nullptr) {             // 第一重检查，避免不必要的加锁，这是一层优化
            lock_guard<mutex> lock(mtx);        // 使用互斥锁，保证只有一个线程进行创建
            if(m_instance == nullptr) {         // 第二重检查，确保只创建一次
                m_instance = new Singleton();   // 创建实例
            }
        }
        return m_instance;
    }

private:
    static Singleton* m_instance;           // 静态实例
    Singleton() {                           // 私有化构造函数
        cout<<"Singleton初始化"<<endl;
    }
    static mutex mtx;
};

Singleton* Singleton::m_instance = nullptr;  //静态成员需要类外初始化，但是因为是懒汉模式，所以初始化为空
mutex Singleton::mtx;                        //静态变量类外初始化

int main() {
    cout<<"单例设计模式"<<endl;
    Singleton* obj = Singleton::getInstance();
    return 0;
}

