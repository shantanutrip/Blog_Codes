# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

#            3 (0,0)

# 9(-1, -1)                         20 (1, -1)
#                       15(0, -2)              7(2, -2)

# 9   (-1,-1,9)
# 3   (0,0,3)
# 15  (0, -2, 15)
# 20  (1, -1, 20)
# 7   (2, -2, 7)

## x - ascending
## y - descending
## val - ascending 


class Solution(object):
    def __init__(self):
        self.tuple_list = []
    
    def dfs(self, node, x, y):
        if node is None:
            return
        self.tuple_list.append((x, -y, node.val))
        self.dfs(node.left, x - 1, y - 1)
        self.dfs(node.right, x + 1, y - 1)
        
        
    def verticalTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        self.dfs(root, 0, 0)
        self.tuple_list.sort()
        sz = len(self.tuple_list)
        ans = []
        temp = []
        for i in range(0, sz):
            if i > 0 and not self.tuple_list[i-1][0] == self.tuple_list[i][0]:
                ans.append(temp)
                temp = []
            temp.append(self.tuple_list[i][2])
        ans.append(temp)
        return ans