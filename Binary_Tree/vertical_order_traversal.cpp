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
    vector<tuple<int, int, int> > res;
    void dfs(TreeNode* node, int x, int y){
        if(node == NULL)
            return;
        res.push_back(make_tuple(x, -y, node -> val));
        dfs(node -> left, x - 1, y - 1);
        dfs(node -> right, x + 1, y - 1);
    }
    bool hasSameXCord(int i, int j){
        return (get<0>(res[i]) == get<0>(res[j]));
    }
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        dfs(root, 0, 0);
        sort(res.begin(), res.end());
        int sz = res.size();
        vector<vector<int> > ans;
        int indx = -1;
        for(int i = 0; i < sz; i++){
            if(i == 0 || (i > 0 && !hasSameXCord(i, i - 1))){
                vector<int> temp;
                ans.push_back(temp);
                indx++;
            }
            ans[indx].push_back(get<2>(res[i]));
        }
        return ans;
    }
};