// ################# C++中内置的堆结构实现
// 主要有
// 1. priority_queue    对应头文件：
#include <queue>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;
void TopK_innerMethod1(vector<int>& vec, int k) {
    // 内置方法 priority_queue
    priority_queue<int, vector<int>, greater<int>>  minHeap;   // priority_queue默认为大根堆，使用geater可以转化为小根堆
    for(int i = 0; i <  vec.size();i++) {
        if(minHeap.size() < k) {
            minHeap.push(vec[i]);
        } else if(vec[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(vec[i]);
        }
    }
    // 打印topK
    while(!minHeap.empty()) {
        int top = minHeap.top();
        cout<<top<<" ";
        minHeap.pop();
    }
}

void TopK_innerMethod2(vector<int>& vec, int k) {
    // C++中内置堆结构实现方法2： 使用堆算法函数，make_heap、push_heap、pop_heap， 需要自定义比较函数
    // 取前k个元素来构建小根堆堆
    vector<int> minHeap(vec.begin(), vec.begin() + k);
    make_heap(minHeap.begin(), minHeap.end(), greater<int>());   //小根堆
    for(auto iter = vec.begin() + k; iter != vec.end(); ++iter) {
        if(*iter > minHeap.front()) {
            // 将堆顶元素移动至末尾
            pop_heap(minHeap.begin(), minHeap.end(), greater<int>());
            // 替换末尾元素
            minHeap.back() = *iter;
            // 将新元素重新插入堆中
            push_heap(minHeap.begin(), minHeap.end(), greater<int>());
        }
    }
    // 此时minHeap保存的就是前k个最大元素，但顺序未必有序
    // 如需排序，可以对heap进行堆排序
    // sort_heap(minHeap.begin(), minHeap.end(), greater<int>()); 
    for(int i = 0; i < k;i++) {
        int top = minHeap.front();
        cout<<top<<" ";
        pop_heap(minHeap.begin(), minHeap.end() - i, greater<int>());
    }
}

class MinHeap
{
public:
    void heapify_up(int index){
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(m_elems[parent] > m_elems[index]) {    // 注意此时满足的条件
                swap(m_elems[parent], m_elems[index]);
                index = parent;
            } else {
                break;
            }
        }
    }
    void heapify_down() {
        // 从上往下调整，都默认从0索引开始
        int index = 0;
        while(index < m_elems.size()) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int min_val;
            if(left >= m_elems.size()) break;
            if(right >= m_elems.size()) min_val = left;   // 注意
            else {
                min_val = m_elems[left] > m_elems[right] ? left: right;
            }
            if(m_elems[index] <= m_elems[min_val]) {
                break;
            } else {
                swap(m_elems[index], m_elems[min_val]);
                index = min_val;
            }
        }
    }

    void push(int num) {
        m_elems.push_back(num);
        heapify_up(m_elems.size() - 1);
    }

    void pop() {
        if(m_elems.size() <= 0) {
            return;
        }
        swap(m_elems.front(), m_elems.back());  // 弹出堆顶元素时，先将最后一个元素与堆顶元素交换再删除
        m_elems.pop_back();
        heapify_down();
    }

    int size() {
        m_size = m_elems.size();
        return m_size;
    }

    int top() {
        if(!m_elems.empty()) {
            return m_elems.front();
        }
    }

    bool empty() {
        return m_elems.empty();
    }

private:
    vector<int> m_elems;   //TopK-->小根堆
    size_t m_size;
};

void TopK_myMethod(vector<int>& vec, int k) {
    // 内置方法 priority_queue
    MinHeap  minHeap;   // priority_queue默认为大根堆，使用geater可以转化为小根堆
    for(int i = 0; i <  vec.size();i++) {
        if(minHeap.size() < k) {
            minHeap.push(vec[i]);
        } else if(vec[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(vec[i]);
        }
    }
    // 打印topK
    while(!minHeap.empty()) {
        int top = minHeap.top();
        cout<<top<<" ";
        minHeap.pop();
    }
}


int main() {
    int n;
    int k;
    vector<int> input;
    cout<<"输入数组的长度："<<endl;
    cin>>n;
    cout<<"输入数组"<<endl;
    for(int i = 0; i< n;i++) {
        int tmp;
        cin>>tmp;
        input.push_back(tmp);
    }

    cout<<"输入K值："<<endl;
    cin>>k;
    // TopK_innerMethod1(input, k);
    // TopK_innerMethod2(input, k);
    TopK_myMethod(input, k);
   
    return 0;
}