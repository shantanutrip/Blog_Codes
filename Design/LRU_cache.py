class DLLNode():
    def __init__(self, key=0, val=0, prev=None, next=None):
        self.key = key
        self.val = val
        self.prev = prev
        self.next = next

class DoublyLinkedList():
    def __init__(self):
        self.head = None
        self.tail = None
        self.elements = 0
    
    def insertEnd(self, key, val):
        newNode = DLLNode(key=key, val=val)
        if self.head is None:
            self.head = newNode
            self.tail = self.head
        else:
            self.tail.next = newNode
            newNode.prev = self.tail
            self.tail = self.tail.next
        self.elements += 1
        return self.tail
    
    def removeNode(self, dllnode):
        if self.elements == 1:
            self.head = None
            self.tail = None
            self.elements = 0
            return 
        
        if dllnode == self.head:
            self.head = self.head.next
            self.head.prev = None
            self.elements -= 1
            return
        
        if dllnode == self.tail:
            self.tail = self.tail.prev
            self.tail.next = None
            self.elements -= 1
            return
        
        dllnode.prev.next = dllnode.next
        dllnode.next.prev = dllnode.prev
        self.elements -= 1
        

class LRUCache(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.capacity = capacity
        self.doublyLinkedList = DoublyLinkedList()
        self.key_to_node = {}
        self.currentElements = 0

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        if key in self.key_to_node and self.key_to_node[key] is not None:
            val = self.key_to_node[key].val
            self.doublyLinkedList.removeNode(self.key_to_node[key])
            self.key_to_node[key] = self.doublyLinkedList.insertEnd(key, val)
            return val
        
        return -1

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: None
        """
        if key in self.key_to_node and self.key_to_node[key] is not None:
            ## IF the key already exists, just update the value and move the key to front
            self.doublyLinkedList.removeNode(self.key_to_node[key])
            self.key_to_node[key] = self.doublyLinkedList.insertEnd(key, value)
            return
        
        ## IF the key doesnt exist
        if self.currentElements == self.capacity:
            ## Remove head or the Least recently used element
            self.key_to_node[self.doublyLinkedList.head.key] = None
            self.doublyLinkedList.removeNode(self.doublyLinkedList.head)
            self.currentElements -= 1
        
        self.key_to_node[key] = self.doublyLinkedList.insertEnd(key, value)
        self.currentElements += 1
        


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)