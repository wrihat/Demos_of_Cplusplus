#include <iostream>
#include <vector>
using namespace std;
// 1. 链表操作: 链表排序
struct ListNode{
    int val;
    ListNode* next;
    ListNode(): val(-1), next(nullptr){}
    ListNode(int value, ListNode* next): val(value), next(next){}
    ListNode(int value): val(value), next(nullptr){}
};

ListNode* getMid(ListNode* head) {
    // 找到链表的中点：
    ListNode* slow = head;
    ListNode* fast = head->next;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode* mergeList(ListNode* head1, ListNode* head2) {
    ListNode* dummyNode = new ListNode( -1);
    ListNode* cur = dummyNode;
    ListNode* p1 = head1;
    ListNode* p2 = head2;
    while(p1 != nullptr && p2 != nullptr) {
        if(p1->val < p2->val) {
            cur->next = p1;
            p1 = p1->next;
        } else {
            cur->next = p2;
            p2 = p2->next;
        } 
        cur = cur->next;
    }
    if(p1!= nullptr) {
        cur->next = p1;
    } else {
        cur->next = p2;
    }
    return dummyNode->next;
}

ListNode* sortList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* mid = getMid(head);  // 找到链表的中点
    ListNode* left = head;
    ListNode* right = mid->next;
    // 先断开链表
    mid->next = nullptr;
    left = sortList(left);
    right = sortList(right);
    return mergeList(left, right);
}





int main() {
    


    return 0;
}




