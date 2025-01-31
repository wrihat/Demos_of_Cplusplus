#include <iostream>

// 1. 定义抽象产品
// 抽象产品A
class AbstractProductA {
public:
    AbstractProductA(){}
    virtual void display() = 0;  // 抽象产品A的纯虚函数
};
// 抽象产品B
class AbstractProductB{
public:
    AbstractProductB(){}
    virtual void show() = 0; // 抽象产品B的纯虚函数
};

// 2. 实现具体产品类
// 具体产品A1类
class ContreteProductA1: public AbstractProductA {
public:
    void display() {
        std::cout<<"create contrete product A1!"<<std::endl;
    }
};

// 具体产品A2类
class ContreteProductA2: public AbstractProductA {
public:
    void display() {
        std::cout<<"create contrete product A2!"<<std::endl;
    }
};

// 具体产品B1类
class ContreteProductB1: public AbstractProductB {
public:
    void show() {
        std::cout<<"create contrete product B1!"<<std::endl;
    }
};

// 具体产品B2类
class ContreteProductB2: public AbstractProductB {
public:
    void show() {
        std::cout<<"create contrete product B2!"<<std::endl;
    }
};

// 3. 定义抽象工厂接口
class AbstractFactory{
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
};

// 4. 实现具体的工厂类
//  具体工厂1，生产产品A1和产品B1
class ContreteFactory1:public AbstractFactory{
public:
    AbstractProductA* createProductA() {
        return new ContreteProductA1(); 
    }

    AbstractProductB* createProductB(){
        return new ContreteProductB1();
    }

};
// 具体工厂2，生产产品A2和产品B2
class ContreteFactory2: public AbstractFactory{
public:
    AbstractProductA* createProductA() {
        return new ContreteProductA2();
    }
    AbstractProductB* createProductB(){
        return new ContreteProductB2();
    }
};

int main( ) {
    // 使用工厂1，生产产品A1和产品B1
    AbstractFactory* factory = new ContreteFactory1();
    AbstractProductA* producta = factory->createProductA();
    AbstractProductB* productb = factory->createProductB();
    producta->display();
    productb->show();
    delete factory;
    delete producta;
    delete productb;
    // 使用工厂2，生产产品A2和茶品B2
    factory = new ContreteFactory2();
    producta = factory->createProductA();
    productb = factory->createProductB();
    producta->display();
    productb->show();
    delete factory;
    delete producta;
    delete productb;
    return 0;
}




