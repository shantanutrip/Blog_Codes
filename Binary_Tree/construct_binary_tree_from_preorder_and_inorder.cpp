/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int preorder_pointer = 0;
    unordered_map<int, int> inorder_position;
    TreeNode* TreeMaker(vector<int>& preorder, vector<int>& inorder, int left, int right){
        if(left > right)
            return NULL;
        if(left == right){
            preorder_pointer++;
            return new TreeNode(inorder[left]);
        }
        int preorder_top_elem = preorder[preorder_pointer];
        int in_pos = inorder_position[preorder_top_elem];
        preorder_pointer++;
        TreeNode* leftNode = TreeMaker(preorder, inorder, left, in_pos - 1);
        TreeNode* rightNode = TreeMaker(preorder, inorder, in_pos + 1, right);
        TreeNode* currentRoot = new TreeNode(preorder_top_elem, leftNode, rightNode); 
        return currentRoot;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int sz = inorder.size();
        for(int i = 0; i < sz; i++)
            inorder_position[inorder[i]] = i;
        return TreeMaker(preorder, inorder, 0, sz - 1);
    }
};