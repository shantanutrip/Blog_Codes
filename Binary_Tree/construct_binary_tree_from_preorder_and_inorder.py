# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

# v : preorder pointer

                                                #            v 
                                                # Preorder - 1 2 3 4 5
                                                # Inorder - [3 2 4 (1) 5]    

            #              v                                                            #                    v 
            # Preorder - 1 2 3 4 5                                                      # Preorder - 1 2 3 4 5    
            # Inorder - [3, (2), 4]	                                                    # Inorder - [(5)]            

#                v              #                  v 
# Preorder - 1 2 3 4 5          # Preorder - 1 2 3 4 5
# Inorder - [(3)]               # Inorder - [(4)]         




class Solution(object):
    def __init__(self):
        self.inorder_location = {}
        self.preorder = []
        self.inorder = []
        self.preorder_pointer = 0
    
    def treeBuilder(self, left, right):
        if left > right:
            return None
        
        if left == right:
            newNode = TreeNode(val = self.preorder[self.preorder_pointer])
            self.preorder_pointer += 1
            return newNode
        
        preorder_element = self.preorder[self.preorder_pointer]
        element_inorder_location = self.inorder_location[preorder_element]
        
        self.preorder_pointer += 1
        
        leftSubtree = self.treeBuilder(left, element_inorder_location - 1)
        rightSubtree = self.treeBuilder(element_inorder_location + 1, right)
        currentRoot = TreeNode(val = preorder_element, left=leftSubtree, right=rightSubtree)
        return currentRoot
            
        
    
    def buildTree(self, preorder, inorder):
        """
        :type preorder: List[int]
        :type inorder: List[int]
        :rtype: TreeNode
        """
        self.preorder = preorder
        self.inorder = inorder
        sz = len(self.preorder)
        for i in range(0, sz):
            self.inorder_location[inorder[i]] = i
        
        return self.treeBuilder(0, sz - 1)
        