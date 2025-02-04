## 一、Qt快速入门
##### 1. QPushButton
    resize()-->尺寸
    move()---->移动

#### 2. Qt对象树
    Qt中的QObject会用对橡树来组织管理
    Qt中的父子关系并不是语法上的继承父子关系

    当父对象析构时，会将子对象都析构掉

3. 声明栈上，但是报错崩溃在堆上
    如果子对象由于系统机制，会自动释放，那么可能存在一个问题，子对象被二次释放导致崩溃，如代码:
```C++
#include <QApplication>
#include "widget.h"
#include <QPushButton>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button;    //虽然是在函数内部声明的，这是在栈上保存，但是QPushButton中的数据是用new在堆上保存的
    Widget w;
    button.setParent(&w);  //设置父对象
    button.setText("主函数中的按钮");
    w.show();
    return a.exec();
}
```
    所以应该在Widget下面声明QPushButton

#### 4. 自定义信号和槽函数
    1）定义一个类Boy，继承自QObject，然后生成的模板头文件中会自带一个signals
    且只用声明，不用实现，在这定义信号

    2）在另一个类Girl中顶一个槽public slots:
    在这个作用域下声明槽函数，槽函数一定要实现

    3）将boy和girl都设置父对象为widget
        接着w.connect(&boy, &Boy::love, &girl, &Girl::ack_love);来连接信号与槽  (发送者对象，发送的信号，接收者对象，接收槽函数)
        然后通过boy.love()调用love信号来触发动作
        其中的信号love不用自己实现，qt环境会自己帮你实现。
        
        信号一定是void类型的

    总结：自定义信号和槽的区别，信号和槽都为void类型，信号只需要定义，不需要实现，但是槽函数既需要定义，也需要实现，信号和槽都可以有参数也都可以重载，Emit是发出信号的标志，也就是在调用语句前加上emit, 如emit boy.love()。



#### 5. 自定义信号带参数重载问题
    信号函数可以有参数，可以重载
    使用connet时可能会造成歧义
    定义一个函数指针：
    ```C++
    void(Boy::*pLove)(QString) = &Boy::love
    ```
    这样用pLove去替换之前的&Boy::love，这样能够防止歧义，另外也可以直接用函数的类型定义去替换，如:
        (void(Boy::*)(QString))&Boy::love   --->  相当于进行数据类型的转换
    utf-8编码问题
    qt对编码的问题
    
#### 6. 信号与槽的扩展
    信号--》信号--》槽
    实现可控
    使用一个按钮，将clicked信号发送，love信号函数接收，然后love发送，ack_love接收
    而且，一个信号可以连接多个槽，多次调用connect即可
    一个槽也可以对应多个信号

    信号的断开，使用disconnect


#### 7. Lambda函数
    信号只需要声明，但是槽函数一定要实现
    用简洁的方式在调用connect时就将槽函数定义好，避免了每次都定义一个独立的函数
    [捕获列表](参数) mutable -> 返回值类型 {函数体}
    捕获列表中：
        空、=、&、this、a、&a、a&b
    默认情况下Lamda函数内是不可更改外部变量值，如需修改则使用mutable关键字

#### 8. Lambda函数扩展
     QString向qDebug中输出的时候是会自动带引号的，可以使用toStdString的方法来变成char*, 也可以用toUtf8


#### 9. QText控件




#### 10. QTextEdit的信号
查看qt助手
    





#### 11. QMainWindow





#### 12. 添加工具栏





#### 13. 添加状态栏





#### 14. 铆接部件、中心部件
在QMainWindow中可以设置铆接、中心、状态栏、菜单栏等部件，已经内置了这些内容，只需要设置或者添加就行



#### 15. UI设计器介绍
UI设计器本质就是xml文件，只不过是它的可视化，如果需要使用ui设计器中的控件，可以使用ui->objName的格式来



#### 16. Qt资源文件的添加
图标的添加有两种方式，可以通过代码方式也可以通过资源文件进行添加
使用代码时可以用setIcon(iconFilePath);但是这个只能使用绝对路径，想要使用相对路径，需要用到资源文件

创建Qtresource file：
    添加前缀，然后通过


#### 17. 对话框---模态和非模态
独占了整个应用的屏幕操作，这样用户就只能操作当前的对话框而无法处理该应用程序中其他的界面。
dlg.exec（）==》模态
dlg.show() ==>非模态




#### 18. QMessageBox
提示、提问、询问、警告四种类型的QMessageBox





#### 19. 基本对话框







## 二、天气预报项目


### 项目设计
#### 1. 退出和拖动



#### 2. 基础控件添加和网格布局



#### 3. 网格控件填充




#### 4. UI设计







### 项目实现










