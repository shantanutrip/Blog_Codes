// Leetcode Question: https://leetcode.com/problems/merge-k-sorted-lists/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
Blog link: https://shantanu-tripathi.medium.com/divide-and-conquer-concept-code-and-practice-problems-86531dd441e

The solution to this problem can also be solved using the 3 step method that we discussed in the blog:

Imagine we have the following list:
[
  1->4->5,
  1->3->4,
  2->6, 
  3->5
]

Lets think in terms of the 3 step method:
1. Base case : When the len(lists) <= 1 

2. 2 Recursive calls, one on left and the other on right half.

3. How to Merge/Combine? -- Use simple merge2lists method as Merge function.

Design a core mergeAllNodes method that merges all the Lists in the given range. Make the left and the right recursive calls. You will get the left_sorted_list and the right_sorted_list. Merge them into 1 by calling the mergeTwoLists method. 

*/
class Solution {
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        ListNode* head = new ListNode(-1); //dummy head
        ListNode* tail = head;
        while(l1 != NULL && l2 != NULL){
            ListNode* newNode = NULL;
            if(l1 -> val <= l2 -> val){
                newNode = new ListNode(l1 -> val);
                l1 = l1 -> next;
            }
            else{
                newNode = new ListNode(l2 -> val);
                l2 = l2 -> next;
            }
            tail -> next = newNode;
            tail = tail -> next;
        }
        if(l1 != NULL){
            tail -> next = l1;
        }
        if(l2 != NULL){
            tail -> next = l2;
        }
        return head -> next;
    }
    
    ListNode* mergeAllNodes(vector<ListNode*>& lists, int left, int right){
        // 1. Base Case
        if(left > right)
            return NULL;
        if(left == right){ 
            return lists[left];
        }
        
        //2. Recursive calls
        int mid = left + ((right - left) >> 1);
        
        ListNode* left_sorted_list = mergeAllNodes(lists, left, mid);
        ListNode* right_sorted_list = mergeAllNodes(lists, mid + 1, right);
        
        //3. Merge the lists into 1.
        ListNode* merged_list = mergeTwoLists(left_sorted_list, right_sorted_list);
        return merged_list;
    }
    
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int sz = lists.size();
        return mergeAllNodes(lists, 0, sz - 1);
    }
};