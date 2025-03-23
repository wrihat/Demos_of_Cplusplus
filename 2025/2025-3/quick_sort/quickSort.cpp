// 快排算法实现
#include <iostream>
#include <vector>
using namespace std;
void quickSort(vector<int>& vec, int start, int end) {
    if(start >= end) return;
    int pivot = vec[start];   // 最开始的元素作为中轴元素
    int left = start;
    int right = end;
    while(left < right) {   // 注意，不用包含=符号，因为需要找到中轴元素的最后位置就是left == right
        while(left < right && vec[right] >= pivot) right--;
        if(left < right) swap(vec[left], vec[right]);
        left++;
        while(left < right && vec[left] <= pivot) left++;
        if(left < right) swap(vec[left], vec[right]);
        right--;
    }
    vec[left] = pivot;
    quickSort(vec, start, left - 1);
    quickSort(vec, left + 1, end);
}


int main() {
    vector<int> input;
    while(true){
        int tmp;
        cin>>tmp;
        if(tmp == -1) break;
        input.push_back(tmp);
    }
    cout<<"输入的数据："<<endl;
    for(int i = 0; i < input.size();i ++) {
        cout<<input[i]<<" ";
    }
    cout<<endl;
    quickSort(input, 0, input.size() -1);
    for(int i = 0; i< input.size();i++) {
        cout<<input[i]<<" ";
    }
    cout<<endl;
    return 0;
}


