/*
 * “So many books, so little time.”
 * ~Frank Zappa
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
 * remove - remove index position from the list and return its value, 
         if index is not a valid position return nil
 * serialized - overwritten, generates the code to reproduce the list.
 */
SerializableSLL := Object clone
SerializableSLL head := Node clone
SerializableSLL length := 0
SerializableSLL append := method(data_,
    if(head next == nil,
         head next = Node clone
         head next data =  data_
         length = length + 1
         ,
         node := head next
         while(node next != nil, node = node next)
         node next = Node clone
         node next data = data_ 
         length = length + 1
    )
    
)
SerializableSLL print := method(
    node := head next
    while(node != nil, node data print; " " print; node = node next)
    "" println
)
SerializableSLL get := method(i,
    count := 0
    node := head next
    while(node next != nil and i > count,node = node next; count = count + 1)
    if(count == i, node data, nil)
)
SerializableSLL set := method(offset,data_,
    count := 0
    node := head next
    while(node next != nil and offset > count,node = node next; count = count + 1)
    if(count == offset, 
        temp := node data; node data = data_; temp, 
        node next = Node clone; length = length + 1;node next data = data_)
)
SerializableSLL remove := method(index,
    count := 0
    prev := head
    node := head next
    while(node next != nil and index > count,node = node next; prev := prev next; count = count + 1)
    if(index == count,
        prev next = node next
        length = length - 1
        node data,
        nil
    ) 
)
SerializableSLL serialized := method(
   code := "SLL clone do("
   node := head next
   while(node != nil, code = code .. "append(" .. node data serialized .. ");"; node = node next)
   code = code .. ")"
   
)