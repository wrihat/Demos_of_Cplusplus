////////////////// 自定义实现堆结构
// 底层存储：vetor
// 对外暴露的接口：push、pop
// 内部方法：heapify_up、heapify_down，向上调整和向下调整，插入时向上调整，弹出时交换后向下调整


#include <iostream>
#include <vector>
using namespace std;
class MinHeap
{
public:
    void heapify_up(int index){
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(m_elems[parent] < m_elems[index]) {
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
            if(right >= m_elems.size()) min_val = right;
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


private:
    vector<int> m_elems;   //TopK-->小根堆
};


int main() {
    MinHeap heap;
    heap.push(10);
    heap.push(20);
    heap.push(15);
    heap.push(30);
    heap.push(25);
    // heap.printHeap();
    // cout<<"弹出堆顶元素："<<endl;
    // cout<<"堆顶元素"<<heap.pop()<<endl;
    // heap.printHeap();




    return 0;
}


