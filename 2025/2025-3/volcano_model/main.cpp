#include <iostream>
#include <vector>

// 定义基础类 Operator
class Operator {
public:
    virtual bool next(std::string& output) = 0; // 抽象函数用于获取下一个元素
};

// 叶子节点：TableScan 模拟从表格读取数据的行为
class TableScan : public Operator {
private:
    std::vector<std::string> data;
    size_t pos;

public:
    TableScan(const std::initializer_list<std::string>& init_data):data(init_data),pos(0){}
    
    bool next(std::string& output) override {
        if(pos >= data.size()) return false;
        output = data[pos++];
        return true;
    }
};

// 非叶子节点 SelectFilter 对输入流施加过滤条件
class SelectFilter : public Operator {
private:
    Operator* child_op_;
    int filter_value_;

public:
    SelectFilter(Operator* op, int value):child_op_(op),filter_value_(value){}

    bool next(std::string& output) override {
        while(child_op_->next(output)){
            // 假设我们有一个非常简单的整数值筛选规则
            try{
                int val = std::stoi(output);
                if(val > filter_value_){
                    return true;
                }
            }catch(...){
                continue;
            }
        }
        return false;
    }

    ~SelectFilter(){
        delete child_op_; // 清理资源
    }
};

int main() {
    // 创建一个包含一些字符串表示数字的虚拟表
    auto table_scan = new TableScan({"1", "2", "3", "4", "5"});
    
    // 添加一个选择过滤器，只保留大于等于3的项目
    auto select_filter = new SelectFilter(table_scan, 3);

    std::string result;
    while(select_filter->next(result)) {
        std::cout << "Filtered Result: " << result << '\n';
    }

    delete select_filter; // 清除内存分配的对象
    
    return 0;
}