/*
LeetCode Question: https://leetcode.com/problems/maximum-subarray/

Lets follow the 3 step approach. In case you are not familiar with it, I recommend
reading the '3 step method' section mentioned in the following blog:

https://shantanu-tripathi.medium.com/divide-and-conquer-concept-code-and-practice-problems-86531dd441e

To summarise, in 3 step method we make a core function. To design that, we need to think of:
1. Base Case
2. 2 Recursive calls
3. How to combine/merge

1. Base Case
In this example, the base case is once again when the length of array is 1. We can't divide the array any further and so we return the element of the array as it is. Technically speaking, in an array with just 1 element, that element itself is the maximum element.

2. Recursive Calls: Simply split the vector into 2 halves and call the recursive function.

3. How to Merge?
This is the major question in all the problems. In this problem, lets assume that we form a core function called maxSubarrayCalculator. This function takes the vector and the index range as an input and calculates the maximum subarray within the index range. 

Now, lets say we know the left and the right maximum subarrays, do you think we can define Merge as:

Merge : max(left_max_subarray, right_max_subarray)

The answer is no!!

Imagine the array is [5, -1, 7, -2]
When we divide it into left and right halves and call
left_max_subarray = maxSubarrayCalculator([5, -1])
right_max_subarray = maxSubarrayCalculator([7, -2])

We get the following:
left_max_subarray = 5
right_max_subarray = 7

And if we go according to our incorrect Merge, our answer would be
max(5, 7) i.e. 7 and it is wrong.

What are we missing??

When we split from the middle: [5, -1,  |Split|  7, -2] 
and then merge using the incorrect merge, we forget to consider the subarrays that start from some index in the left split and span over some index in the right split. Let us call them OverlappingSubarrays.

In our case, the overlapping subarray that gives us the answer is:

[5, -1,  |Split|  7, -2] 
 ^                ^
Start             End

i.e. (5) + (-1) + (7) = 11

Thus, we need to change our merge function slightly. 

Our merge function will look like:

Merge: max(left_max_subarray, right_max_subarray, maxOverlappingSubarraySum(array))

Where maxOverlappingSubarraySum will be a helper function that finds the maxOverlappingSubarray for a given array in the following way: 
1. takes in an array, 
2. finds midpoint
3. moves left from the middle point to find the maximum_left_suffix_sum of the left half 
4. moves right from the middle point to find the maximum_right_prefix_sum of the right half.
5. returns maximum_left_suffix_sum + maximum_right_prefix_sum

Lets go through the code
*/

class Solution {
    
    int maxOverlappingSubarraySum(vector<int>& nums, int left, int right){
        int mid = left + ((right - left)/2);
        int left_max_suffix_sum = INT_MIN;
        int sum = 0;
        for(int i = mid; i >= left; i--){
            sum += nums[i];
            left_max_suffix_sum = max(left_max_suffix_sum, sum);
        }
        
        int right_max_prefix_sum = INT_MIN;
        sum = 0;
        for(int i = mid + 1; i <= right; i++){
            sum += nums[i];
            right_max_prefix_sum = max(right_max_prefix_sum, sum);
        }
        
        return left_max_suffix_sum + right_max_prefix_sum;
    }
    //Core function called maxSubarrayCalculator.
    //This function takes the vector and the index range as an input and calculates the maximum subarray within the index range. 
    int maxSubarrayCalculator(vector<int>& nums, int left, int right){
        // 1. Base Case
        if(left == right){
            return nums[left];
        }
        
        int mid = left + ((right - left)/2);
        
        // 2. Recursive Calls
        int left_max_subarray = maxSubarrayCalculator(nums, left, mid);
        int right_max_subarray = maxSubarrayCalculator(nums, mid + 1, right);
        
        // 3. Combine/Merge step
        int max_overlapping_sum = maxOverlappingSubarraySum(nums, left, right);
        return max(max_overlapping_sum, max(left_max_subarray, right_max_subarray));
    }
    
public:
    int maxSubArray(vector<int>& nums) {
        int sz = nums.size();
        return maxSubarrayCalculator(nums, 0, sz - 1);
    }
};