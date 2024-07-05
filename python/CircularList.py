#!/usr/bin/env python3

"""
   Imagination is more important than knowledge. 
   For knowledge is limited to all we now know and understand,
   while imagination embraces the entire world,
   and all there ever will be to know and understand.
   ~ Albert Einstein
"""


class CircularList:
    """
       CicrularList based on pythons built in list
    """

    def __init__(self):
        self.array = []

    def __str__(self):
        " Return string representation of the list "
        return str(self.array)

    def __len__(self):
        " return length of the list "
        return len(self.array)

    def __getitem__(self, index):
        " get indexth element of the list "
        return self.array[self.get_index(index)]

    def __setitem__(self, index, value):
        " set indexth element of the list "
        self.array[self.get_index(index)] = value

    def get_index(self, index):
        " get the actual index of the list or raise IndexError if list is empty"
        if (len(self.array) == 0):
            raise IndexError("List index out of range")
        elif (index < 0):
            length = len(self.array) * -1
            while (index < length):
                index += len(self.array)
            return index
        elif (index < len(self.array)):
            return index
        else:
            length = len(self.array)
            index = index % length
            return index

    def append(self, item):
        " append item to the list "
        return self.array.append(item)

    def pop(self):
        " pop last item from the list "
        return self.array.pop()

    def __iter__(self):
        " allow for iteration through the list "
        return iter(self.array)
