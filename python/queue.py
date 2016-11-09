#!/usr/bin/env python3

# "Man is still the most extraordinary computer of all." ~ John F. Kennedy

class QNode:
    """ Node for Queue """
    def __repr__(self):
        return "<Queue node object>"

    def __init__(self,data=None):
        self.next = None
        self.data = data
        
class Queue:
    """ Queue class """
    def __init__(self):
        self.size = 0
        self.head = QNode()
        self.last = self.head
    
    def __str__(self):
        string = "<"
        node = self.head.next
        while node:
            string += " " + str(node.data)
            node = node.next
        string += ">"
        return string

    def __iter__(self):
        """ iterate through queue using a for loop """
        return self

    def __next__(self):
        """ return next element of queue using built in next() method """
        return self.pop()

    def append(self,data):
        """ add last element into quque """
        node = QNode(data)
        self.last.next = node
        self.last = node
        self.size += 1

    def pop(self):
        """ Pop the first element in the queue """
        if self.head.next:
            to_pop = self.head.next
            self.head.next = to_pop.next
            self.size -= 1
            return to_pop.data
        else:
            raise StopIteration("Queue is empty")

    def length(self):
        """ return size of Queue """
        return self.size

    def is_empty(self):
        """ returns if queue is empty """
        return self.size == 0

    def __len__(self):
        """ return length of queue using built in len() method """
        return self.length()

