#include <iostream>

//产品类(抽象类，不能实例化)
class Product{
public:
    Product(){}
    virtual void show() = 0;  //纯虚函数
};

// 抽象类
class Factory {
public:
    virtual Product* createProduct() = 0;  //纯虚函数
};

// 产品A
class ProductA: public Product {
public:
    ProductA(){}
    void show(){
        std::cout<<"pdroduct A create!"<<std::endl;
    }
};

//产品B
class ProductB: public Product {
public:
    ProductB(){}
    void show() {
        std::cout<<"product B create!"<<std::endl;
    }

};

// 工厂A，只生产A
class FactoryA: public Factory{
public:
    Product* createProduct(){
        Product* product_ = nullptr;
        product_ = new ProductA();
        return product_;
    }
};

// 工厂B，只生产B
class FactoryB: public Factory{
public:
    Product* createProduct(){
        Product* product_ = nullptr;
        product_ = new ProductB();
        return product_;
    }
};


int main() {
    Product* product_ = nullptr;
    auto MyFactoryA = new FactoryA();
    product_ = MyFactoryA->createProduct();     // 调用产品A的工厂来生产A产品
    product_->show();
    delete product_;
    auto MyFactoryB = new FactoryB();
    product_ = MyFactoryB->createProduct();     // 调用产品B的工厂来生产B产品
    product_->show();
    delete product_;
    return 0;
}


