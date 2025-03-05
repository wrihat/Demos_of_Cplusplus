#include <iostream>
#include <queue>
#include <memory>
#include <list>
#include <vector>
using namespace std;

int main() {
    vector<shared_ptr<pair<int, int>>> list_;
    shared_ptr<pair<int, int>> item1 =  make_shared<pair<int, int>>(1, 2);
    shared_ptr<pair<int, int>> item2 = make_shared<pair<int, int>>(3, 4);
    list_.push_back(item1);
    cout<<"item1的引用计数为: "<<item1.use_count()<<endl;
    cout<<"item2的引用计数为:" <<item2.use_count()<<endl;
    list_[0] = item2;
    cout<<"item1的引用计数为: "<<item1.use_count()<<endl;
    cout<<"item2的引用计数为:" <<item2.use_count()<<endl;
    return 0;
}