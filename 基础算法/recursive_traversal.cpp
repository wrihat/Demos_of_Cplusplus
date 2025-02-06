// 递归方式实现二叉树的遍历
#include <iostream>
#include <vector>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// void preorder_recer

void preorderTree(TreeNode* root, vector<int>& vec) {
    if(root == nullptr) return;
    vec.push_back(root->val);
    preorderTree(root->left, vec);
    preorderTree(root->right, vec);
}
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> vec;
    preorderTree(root, vec);
    return vec;
}

void inorderTree(TreeNode* root, vector<int>& vec) {
    if(root == nullptr) return;
    inorderTraversal(root->left);
    vec.push_back(root->val);
    inorderTree(root->right, vec);
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> vec;
    inorderTree(root, vec);
    return vec;
}

void postorderTree(TreeNode* root, vector<int>& vec) {
    if(root == nullptr) return;
    postorderTree(root->left, vec);
    postorderTree(root->right, vec);
    vec.push_back(root->val);
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> vec;
    postorderTree(root, vec);
    return vec;
}


int main() {




    return 0;
}

