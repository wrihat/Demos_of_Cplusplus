#include <iostream>
#include <string>
#include <pthread.h>

//产品类，抽象类，不能实例化，作为一个所有都需实现的接口
class Product{
public:
    Product(){};
    virtual void show() = 0; // 纯虚函数
};

// 产品A
class ProductA: public Product {
public:
    ProductA(){};
    void show() {
        std::cout<<"product A create!"<<std::endl;
    }
    
};

class ProductB: public Product {
public:
    ProductB(){};
    void show() {
        std::cout<<"product B create!"<<std::endl;
    }
};

class SimpleFactory{
public:
    SimpleFactory(){};
    Product* createProduct(const std::string str) {
        if(str == "Product A") {
            return new ProductA();
        } 
        if(str == "Product B") {
            return new ProductB();
        }
        return nullptr;
    }

};

int main() {
    SimpleFactory factory;      //工厂对象
    Product* product;           //产品   
    product = factory.createProduct("Product A");
    product->show();
    delete product;
    product = factory.createProduct("Product B");
    product->show();
    delete product;
    return 0;
}


