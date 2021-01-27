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
    bool checkValidity(TreeNode* node, int min_val, int max_val){
        if(node == NULL)
            return true;
        if(min_val > max_val)
            return false;
        int curr_val = node -> val;
        if((curr_val == INT_MIN && node -> left != NULL) || 
           (curr_val == INT_MAX && node -> right != NULL))
            return false;
        bool c1 = (curr_val == INT_MIN) ||  checkValidity(node -> left, min_val, curr_val - 1); 
        // 2nd half not checked if first is true. 
        // This condition is required bcoz, if curr_val is INT_MIN, then curr_val - 1 will throw error
        bool c2 = (curr_val == INT_MAX) ||  checkValidity(node -> right, curr_val + 1, max_val);
        return c1 && c2 && min_val <= curr_val && curr_val <= max_val;
    }
public:
    bool isValidBST(TreeNode* root) {
        return checkValidity(root, INT_MIN, INT_MAX);
    }
};