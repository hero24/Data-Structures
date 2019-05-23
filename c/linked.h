#include <stdlib.h>
/*
 * "Z oddali nasze godziny szkolne błękitnieją" ~ Kornel Makuszyński
 */
struct Node {
	int val;
	struct Node* next;
};

typedef void (*void_callback)(int val);
typedef int (*ret_callback)(int val);
typedef int (*reducer_callback)(int val, int acc);
typedef struct Node* list;

int free_nodes(struct Node* ptr){
	//frees all the nodes
	if (ptr == NULL){
		return 0;
	} else {
		int ret = free_nodes(ptr->next);
		free(ptr);
		ptr->next = NULL;
		return ret;
	}
}

struct Node* add_elem(int val, struct Node* ptr){
	// adds element to the end of the list
	struct Node *n = (struct Node*) malloc(sizeof(struct Node));
	ptr->next = n;
	n->val = val;
	n->next = NULL;
	return n;
}

static int rem_next_elem(struct Node* prev){
	// removes next element from the list and returns its value
	struct Node *n = prev->next;
	int val;
	prev->next = n->next;
	val = n->val;
	free(n);
	return val;
}

struct Node* get_node(int i, struct Node* n){
  // retrieves node at index i
	struct Node* node;
	for(node=n;i!=0 && node!=NULL;i--){
		node = node->next;
	}
	return node;
}

struct Node* set_node(int index, int val, struct Node* n){
  // sets value of node at index i
	struct Node* node = get_node(index, n);
	node->val = val;
	return node;
}

int rem_node(int index, struct Node* n){
  // removes node at index i and returns its value
	return rem_next_elem(get_node(index-1,n));
}

struct Node* add_node(int index, int val, struct Node* n){
  // adds node at index i with value val
	struct Node *m, *node;
	m = get_node(index-1, n);
	node = m->next;
	m = add_elem(val, m);
	m->next = node;
	return m;
}

int length(struct Node* n){
  // returns length of list
	struct Node* node;
	int len;
	for(node = n, len=0; node != NULL; node=node->next,len++);
	return len;
}

struct Node* create_list(int init_val){
  // creates new list with initial value init_val at index 0
	struct Node *n = (struct Node*) malloc(sizeof(struct Node));
	n->val = init_val;
	n->next = NULL;
	return n;
}

void walk_through(struct Node* lst, void_callback func){
  // walk through the list and call func on value of each cell in list
	struct Node* node;
	for(node=lst; node!=NULL; node=node->next){
		func(node->val);
	}
}

void map(struct Node* lst, ret_callback func){
  // walk though the list, call func on each value and 
  // set the result as value at given index
	struct Node* node;
	for(node=lst; node!=NULL; node=node->next){
		node->val = func(node->val);
	}
}

int reduce(struct Node* lst, reducer_callback func){
  // call func on all the values of the list and return result
	struct Node* node;
	int acc = lst->val;
	for(node=lst->next; node!=NULL; node=node->next){
		acc = func(node->val, acc);
	}
	return acc;
}

int contains(struct Node* lst, int val){
  // check if list contains val, return index at which the value is
  // stored or -1 otherwise.
	struct Node* node = lst;
	int index = 0;
	do {
		if (node->val == val)
			return index;
		index++;
	} while ((node=node->next) != NULL);
	return -1;
}
