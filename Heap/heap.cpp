#include <iostream>
#include <vector>
using namespace  std;
class MaxHeap{  //大根堆
private:
    vector<int> m_heap;  //使用vector进行数据存储
public:
    // 针对堆结构的维护：
    // 从最后面插入数据、向上调整
    // 从堆顶(首元素)弹出元素、用最后的元素进行填充、向下调整
    void heapfiy_up(int index) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(m_heap[parent] < m_heap[index]) {
                swap(m_heap[parent], m_heap[index]);
                index = parent;
            } else break;
        }
    }

    void heapfiy_down() {
        int index = 0;
        while( index < m_heap.size()) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;  
            if(right < m_heap.size()) {
                int max_index = m_heap[left] > m_heap[right] ? left: right;
                if(m_heap[index] < m_heap[max_index]) {
                    swap(m_heap[index], m_heap[max_index]);
                    index= max_index;
                } else break;
            } else if(left < m_heap.size()) {
                int max_index = left;
                if(m_heap[index] < m_heap[max_index])  {
                    swap(m_heap[index], m_heap[max_index]);
                    index = max_index;
                } else break;
            } else break;
        }
    }

    void push(int value) {
        m_heap.push_back(value);
        heapfiy_up(m_heap.size() - 1);
    }

    int pop() {
        if(m_heap.size() <= 0) return -1;
        int pop_value = m_heap[0];   
        swap(m_heap[0], m_heap[m_heap.size() - 1]);
        m_heap.pop_back();
        heapfiy_down();
        return pop_value;
    }
    void printHeap() {
        for(auto& num: m_heap) {
            cout<<num<<" ";
        }
    }
};   


int main() {
    MaxHeap heap;
    heap.push(10);
    heap.push(20);
    heap.push(15);
    heap.push(30);
    heap.push(25);
    heap.printHeap();
    cout<<"弹出堆顶元素："<<endl;
    cout<<"堆顶元素"<<heap.pop()<<endl;
    heap.printHeap();


    return 0;
}