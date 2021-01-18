class Solution(object):    
    def sortArray(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        return self.sort(nums)
    
    ## Lets define the core function first
    def sort(self, arr):
        """
        :type arr: List[int]
        :rtype: List[int]
        """
        sz = len(arr)
        
        ####################################################################
        ####################### 1. Base Case handled  ######################
        ####################################################################
        if sz == 1:
            return arr
        
        ####################################################################
        ################## 2. Make recursive calls on each halves ##########
        ####################################################################
        mid = sz/2
        left_sorted = self.sort(arr[:mid]) 
        right_sorted = self.sort(arr[mid:])
        ## While making the above recursive calls, do not think how self.sort will behave
        ## Just consider self.sort() as a black box for that moment
        
        ####################################################################
        ################### 3. Call the merge function #####################
        ####################################################################
        return self.merge(left_sorted, right_sorted)
    
    ## Once the core function is designed, go on to implement the merge function
    def merge(self, left_sorted, right_sorted):
        """
        :type left_sorted: List[int]
        :type right_sorted: List[int]
        :rtype: List[int]
        """
        ## Declare a combined_list that will be returned at the end
        combined_list = []
        ## Find the size of both the input lists 
        ## Declare 2 pointers -- left_index, right_index -- for both the lists respectively
        left_size = len(left_sorted)
        right_size = len(right_sorted)
        left_index = 0
        right_index = 0
        ## Till the time none of the pointers have exceeded the total size,
        ## select the smaller value, append it to the list and increment the pointer
        while(left_index < left_size and right_index < right_size):
            if left_sorted[left_index] <= right_sorted[right_index]:
                combined_list.append(left_sorted[left_index])
                left_index += 1
            else:
                combined_list.append(right_sorted[right_index])
                right_index += 1
        
        ## Once we come out of the above while loop, atmost 1 of the 2 lists has an element left in it
        ## Therefore, the control just enter in either of the 2 loops given below
        while(left_index < left_size):
            combined_list.append(left_sorted[left_index])
            left_index += 1
        
        while(right_index < right_size):
            combined_list.append(right_sorted[right_index])
            right_index += 1
        
        return combined_list