/*
 * "I don't believe in having regrets" ~ Slash
 */
 
# Node for Singly Linked List
Node := Object clone
Node data := nil
Node next := nil

# Singly Linked List
/*
 * length - the length of the list
 * append - appends element to the end of the list
 * print - prints out the contents of the list
 * get - returns ith element of the list or nil i is invalid index value
 * set - sets offset field in the list to data_ or if offset does not exists, 
 *       appends data_ to the end of the list.
 */
SLL := Object clone
SLL head := Node clone
SLL length := 0
SLL append := method(data_,
    if(head next == nil,
         head next = Node clone
         head next data =  data_,
         node := head next
         while(node next != nil, node = node next)
         node next = Node clone
         node next data = data_ 
         length = length + 1
    )
    
)
SLL print := method(
    node := head next
    while(node != nil, node data print; " " print; node = node next)
    "" println
)
SLL get := method(i,
    count := 0
    node := head next
    while(node next != nil and i > count,node = node next; count = count + 1)
    if(count == i, node data, nil)
)
SLL set := method(offset,data_,
    count := 0
    node := head next
    while(node next != nil and offset > count,node = node next; count = count + 1)
    if(count == offset, 
        temp := node data; node data = data_; temp, 
        node next = Node clone; length = length + 1;node next data = data)
)
# development test code
/*
myList := SLL clone
myList append(10)
myList append(11)
myList append(12)
myList length println
myList get(2) println
myList get(3) println
myList set(2,14)
myList print
*/