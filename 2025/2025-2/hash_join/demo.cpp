#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

// 元组结构体
struct Tuple {
    int user_id;
    std::string name;
    int order_id;
    double amount;

    Tuple(int uid, std::string n, int oid, double a)
        : user_id(uid), name(std::move(n)), order_id(oid), amount(a) {}
};

// 抽象算子接口
class Operator {
public:
    virtual ~Operator() = default;
    virtual std::shared_ptr<Tuple> Next() = 0;
};

// 模拟数据源的 Scan 算子
class ScanOperator : public Operator {
    std::vector<std::shared_ptr<Tuple>> data_;
    size_t cursor_ = 0;
public:
    explicit ScanOperator(std::vector<std::shared_ptr<Tuple>> data)
        : data_(std::move(data)) {}

    std::shared_ptr<Tuple> Next() override {
        return (cursor_ < data_.size()) ? data_[cursor_++] : nullptr;
    }
};

// Hash Join 算子
class HashJoinOperator : public Operator {
    std::unique_ptr<Operator> left_;   // 构建表（如 users）
    std::unique_ptr<Operator> right_;  // 探测表（如 orders）
    std::unordered_multimap<int, std::shared_ptr<Tuple>> hash_table_;
    std::shared_ptr<Tuple> current_right_tuple_ = nullptr;
    decltype(hash_table_.begin()) current_hash_entry_;
    bool build_phase_done_ = false;

    void BuildPhase() {
        while (auto tuple = left_->Next()) {
            hash_table_.emplace(tuple->user_id, tuple);
        }
        build_phase_done_ = true;
    }

public:
    HashJoinOperator(std::unique_ptr<Operator> left, std::unique_ptr<Operator> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    std::shared_ptr<Tuple> Next() override {
        if (!build_phase_done_) {
            BuildPhase();
        }

        while (true) {
            if (!current_right_tuple_) {
                current_right_tuple_ = right_->Next();
                if (!current_right_tuple_) return nullptr; // 探测表耗尽
                auto range = hash_table_.equal_range(current_right_tuple_->user_id);
                current_hash_entry_ = range.first;
            }

            // 遍历当前右表元组的所有匹配项
            if (current_hash_entry_ != hash_table_.end() &&
                current_hash_entry_->first == current_right_tuple_->user_id) {
                // 合并左右元组
                auto left_tuple = current_hash_entry_->second;
                auto joined_tuple = std::make_shared<Tuple>(
                    left_tuple->user_id,
                    left_tuple->name,
                    current_right_tuple_->order_id,
                    current_right_tuple_->amount
                );
                ++current_hash_entry_;
                return joined_tuple;
            } else {
                current_right_tuple_ = nullptr; // 当前右表元组处理完成
            }
        }
    }
};

// 示例数据
int main() {
    // 构建 users 表（左表）
    std::vector<std::shared_ptr<Tuple>> users = {
        std::make_shared<Tuple>(1, "Alice", 0, 0.0),
        std::make_shared<Tuple>(2, "Bob", 0, 0.0)
    };

    // 构建 orders 表（右表）
    std::vector<std::shared_ptr<Tuple>> orders = {
        std::make_shared<Tuple>(0, 1, 1001, 99.9),
        std::make_shared<Tuple>(0, 2, 1002, 199.9),
        std::make_shared<Tuple>(0, 1, 1003, 299.9)
    };

    auto hash_join = std::make_unique<HashJoinOperator>(
        std::make_unique<ScanOperator>(std::move(users)),
        std::make_unique<ScanOperator>(std::move(orders))
    );

    // 执行查询
    while (auto tuple = hash_join->Next()) {
        std::cout << "UserID: " << tuple->user_id
                  << ", Name: " << tuple->name
                  << ", OrderID: " << tuple->order_id
                  << ", Amount: " << tuple->amount << std::endl;
    }
    
    return 0;
}