// 非递归方式实现二叉树的遍历

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// 前序遍历
vector<int> preorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    vector<int> vec;
    if(root == nullptr) return vec;
    st.push(root);
    while(!st.empty()) {
        TreeNode* cur = st.top();
        st.pop();
        vec.push_back(cur->val);
        // 注意因为栈是先进后出，所以先将右子树入栈，后将左子树入栈
        if(cur->right) st.push(cur->right);
        if(cur->left) st.push(cur->left);
    }
    return vec;
}

// 中序遍历

vector<int> inorderTraversal(TreeNode* root) {
    TreeNode* cur = root;
    stack<TreeNode*> st;
    vector<int> vec;
    while(cur != nullptr || !st.empty()){
        if(cur != nullptr) {  // 如果还没有遍历到叶子节点，则继续遍历
            st.push(cur);
            cur = cur->left;
        } else {
            cur = st.top();
            st.pop();
            vec.push_back(cur->val);
            cur = cur->right;
        }
    }
    return vec;
}


// 后序遍历

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> vec;
    stack<TreeNode*> st;
    if(root == nullptr) return vec;
    st.push(root);
    while(!st.empty()) {
        TreeNode* cur = st.top();
        vec.push_back(cur->val);
        if(root->right) st.push(root->right);
        if(root->left)st.push(root->left);
    }
    reverse(vec.begin(), vec.end());
    return vec;
}


// 层次遍历
vector<vector<int>> leveOrderTraversal(TreeNode* root) {
    queue<TreeNode*> que;
    vector<vector<int>> vec;
    if(root == nullptr) return vec;
    que.push(root);
    while(!que.empty()) {
        vector<TreeNode*> levelNodes;
        vector<int> levelVals;
        while(!que.empty()) {
            levelVals.push_back(que.front()->val);
            levelNodes.push_back(que.front());
            que.pop();
        }
        vec.push_back(levelVals);
        for(int i = 0; i < levelNodes.size(); i++) {
            if(levelNodes[i]->left) que.push(levelNodes[i]->left);
            if(levelNodes[i]->right) que.push(levelNodes[i]->right);
        }
    }
    return vec;
}


int main() {




    return 0;
}

