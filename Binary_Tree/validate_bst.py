# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

#                            2 [-inf, inf]
# 1 [-inf, 1]                                           3 [3, inf]

class Solution(object):
    def checkValidity(self, node, min_val, max_val):
        if node is None:
            return True
        
        return (node.val <= max_val 
                and node.val >= min_val
                and self.checkValidity(node.left, min_val, node.val - 1)
                and self.checkValidity(node.right, node.val + 1, max_val))
    
    def isValidBST(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        return self.checkValidity(root, -sys.maxint - 1 , sys.maxint)
        