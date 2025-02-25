## 易道云-云助教项目---客户端部分
###  项目笔记
1. 项目拆解
系统设计：
    整体采用常见的分布式微服务架构,包含四个组成部分：
    负载均衡服务器、登录服务器、信令服务器、流服务器
    细分拆解为6个模块：
    网络模块、负载模块、登录模块、信令模块、流模块、UI模块

### 项目遇到的问题
#### 1. 针对客户端qt中ffmpeg库的导入
能够正确引入头文件，但是没法链接到对应的库
gpt给出的解决方案：
    1）确认库文件路径和文件格式
    2）检查动态库的运行时路径
    3）检查链接顺序
    4）检查是否漏掉必要库
    5）验证工具链与库的兼容性
    6）强制重新运行去qmake

将pro中关于ffmpeg的相关配置都删除后依然报同样的错误，所以不需要在pro项目文件中加入头文件相关的配置(已经在系统的环境变量中添加了), 最终要的时解决库文件的链接失败问题
1. 检查dll库是否存在或文件名正确
2. 将对应dll放入到对应的目录下

在ffmpeg的lib文件夹下有三种文件，如avformat对应的库：
avformat.lib
> 静态库或导入库（Import Library）
用途：
在链接阶段，链接器会使用 .lib 文件来解析程序中对 avformat 函数的引用。
它可能是静态库也可能是动态库，区分： \
- 如果 FFmpeg 的安装包含 .dll 文件（如 avformat.dll），那么 .lib 通常是导入库。
- 如果 FFmpeg 的安装中没有 .dll，则 .lib 很可能是静态库

avformat-60.def
>这是模块定义文件
用途：
提供动态链接库导出信息
描述了哪些符号可以被外部程序访问
是动态库的辅助文件, 通常用作链接时的输入文件


libavformat.dll.a
>这是动态导入库，专门为MinGW编译器使用的文件类型
它是一个中间文件，用于告诉链接器如何在程序运行时调用动态库（.dll 文件）的函数。 \
本身不包含函数的实现，只包含符号表和导出信息，用于连接 .dll 文件。 \
它与动态链接库 libavformat.dll 配套使用。
在运行时，程序通过 libavformat.dll.a 中的信息加载并调用 libavformat.dll 中的函数。

* .dll.a文件与.lib文件的区别 \
.lib文件通常是MSVC编译器生成的导入库
.dll.a文件是MinGW编译器生成的导入库


使用MinGW编译器时，通常包含下面三种文件：
```
1. 动态链接库文件（.dll）:
包含函数的实现。
运行时被加载到程序的内存中。
示例: libavformat.dll。
2. 导入库文件（.dll.a 或 .lib）:
提供 .dll 文件的导出符号信息。
供编译器和链接器在编译阶段使用。
示例: libavformat.dll.a 或 avformat.lib。
3. 头文件（.h 或 .hpp）:
定义函数的声明和必要的结构体，用于代码编写。
示例: libavformat/avformat.h。
```


#### 2. qt Creator中MSVC编译器的引入



