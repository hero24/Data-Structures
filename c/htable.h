#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef HASH_SIZE
#define HASH_SIZE 20
#endif

#ifndef HASH_TYPE
#define HASH_TYPE int
#endif
/*
 * HashTable implementation in C.
 * Warning liable to buffer overflows as it uses unsafe 
 * strcmp function for string comparesings.
 *
 * "Live your life by a compass not a clock." ~ Stephen Covey
 */

struct Bucket {
	union {
		char* key __attribute__((aligned(8)));
		unsigned long long int hash __attribute__((aligned(8)));
	} key __attribute__((aligned(8)));
	HASH_TYPE* value __attribute__((aligned(8)));
	struct Bucket* next __attribute__((aligned(8)));
} __attribute__((aligned(32)));

struct HashHead {
	struct Bucket* bucket_array[HASH_SIZE] __attribute__((aligned(256)));
	int object_count __attribute__((aligned(8)));
	int (*hashf)(char*) __attribute__((aligned(8)));
} __attribute__((aligned(256)));

typedef struct HashHead* HashTable;
typedef int(hash_callback)(char*);

static int get_hash(char* key, struct HashHead* hash){
	/*
	 * computes index using given hash function or 
	 * the default index computation
	 */
	int index;
	if (hash->hashf){
		index = hash->hashf(key);
		if(index >= HASH_SIZE)
			index = index % HASH_SIZE;
	}
	else
		index = ((unsigned long long int) key) % HASH_SIZE;
	return index;

}

struct HashHead* create_hash(hash_callback hash_func){
	/*
	 * Initializes hash table. Returns HashTable object.
	 * [optional] -> hash function to use for hashing.
	 */
	struct HashHead *hash = malloc(sizeof(struct HashHead));
	int i;
	hash->object_count = 0;
	hash->hashf = hash_func;
	for(i=0; i<HASH_SIZE; i++){
		hash->bucket_array[i] = NULL;
	}
	return hash;
}

struct HashHead* add_element(char* key, HASH_TYPE* val, struct HashHead* hash){
	/*
	 * Adds value val to HashTable with lookup key of key.
	 * Returns HashTable.
	 */
	int index = get_hash(key, hash);
	struct Bucket* bucket = malloc(sizeof(struct Bucket));;
	bucket->key.key = key;
	bucket->value = val;
	hash->object_count++;
	if (hash->bucket_array[index] == NULL){
		bucket->next = NULL;
		hash->bucket_array[index] = bucket;
	} else {
		bucket->next = hash->bucket_array[index];
		hash->bucket_array[index] = bucket;
	}
	return hash;
}

static struct Bucket* get_bucket(char* key, struct HashHead* hash){
	/*
	 * Retrieves bucket that stores value identified by given key.
	 */
	int index = get_hash(key, hash);
	struct Bucket* bucket = hash->bucket_array[index];
	while (bucket != NULL && (strcmp(bucket->key.key,key)!=0)){
		bucket = bucket->next;
	}
	return bucket;
}

HASH_TYPE* get_element(char* key, struct HashHead* hash){
	/*
	 * Returns value stored under given key.
	 */
	struct Bucket* bucket = get_bucket(key, hash);
	if (bucket != NULL){
		return bucket->value;
	}
	return NULL;
}

int size(struct HashHead* hash){
	/*
	 * returns the size (object count) of HashTable
	 */
	return hash->object_count;
}

int is_empty(struct HashHead* hash){
	/*
	 * Checks if HashTable is empty.
	 */
	return hash->object_count == 0;
}

HASH_TYPE* get_or_default(char *key, HASH_TYPE* _default, struct HashHead* hash){
	/*
	 * Get element stored at key from HashTable, if it doesnt exist
	 * erturn _default value.
	 */
	HASH_TYPE* elem = get_element(key, hash);
	if (elem == NULL)
		return _default;
	return elem;
}

int contains_key(char* key, struct HashHead* hash){
	/*
	 * Check if given key is in HashTable.
	 */
	struct Bucket* bucket = get_bucket(key, hash);
	return bucket != NULL;
}

HASH_TYPE* replace(char* key, HASH_TYPE* value, struct HashHead* hash){
	/*
	 * Replace value stored at given key with given value.
	 * Return old value.
	 */
	struct Bucket* bucket = get_bucket(key, hash);
	if(bucket == NULL)
		return NULL;
	HASH_TYPE* prev = bucket->value;
	bucket->value = value;
	return prev;
}

HASH_TYPE* replace_or_create(char* key, HASH_TYPE* val, struct HashHead* hash){
	/*
	 * Replace value stored at given key with given value.
	 * If it doesnt exist create new entry.
	 * Return previous value or 0.
	 */
	HASH_TYPE* ret = replace(key, val, hash);
	if (ret)
		return ret;
	add_element(key, val, hash);
	return 0;
}

char* contains_value(HASH_TYPE* val, struct HashHead* hash){
	/*
	 * Check if HashTable contains given value
	 * if it does return the key that stores it.
	 */
	int i;
	HASH_TYPE v = *val;
	struct HashHead hh = *hash;
	struct Bucket* b;
	for(i=0; i < HASH_SIZE; i++){
		if( (b=hh.bucket_array[i]) == NULL )
			continue;
		while (b != NULL){
			if(*(b->value) == *val)
				return b->key.key;
			b = b->next;
		}
	}
	return NULL;
}

char** get_keys(int* ret_size, struct HashHead* hash){
	/*
	 * return list of all the keys in HashTable.
	 * Gets ret_size which is set to the size of returned list.
	 */
	int i,j;
	struct HashHead hh = *hash;
	struct Bucket* b;
	char** keys = malloc(sizeof(char*) * hash->object_count);
	for(i=0,j=0; i<HASH_SIZE; i++){
		if((b=hh.bucket_array[i]) == NULL)
			continue;
		while (b!=NULL){
			*(keys+j) = b->key.key;
			b=b->next;
			j++;
		}
	}
	*ret_size = hash->object_count;
	return keys;
}

HASH_TYPE* remove_entry(char* key, struct HashHead* hash){
	/*
	 * Remove key and value that it points to from HashTable.
	 * return value pointed to by given key.
	 */
	int index = get_hash(key, hash);
	struct Bucket* bucket = hash->bucket_array[index];
	struct Bucket* prev = NULL;
	HASH_TYPE* val = NULL;
	while (bucket != NULL && strcmp(bucket->key.key, key)){
		prev = bucket;
		bucket = bucket->next;
	}
	if (bucket != NULL && bucket->next != NULL){
		if (prev != NULL)
			prev->next = bucket->next;
	 	else
	 		hash->bucket_array[index] = bucket->next;
	} else {
		hash->bucket_array[index] = NULL;
	}
	if(bucket != NULL){
		hash->object_count--;
		val = bucket->value;
	}
	free(bucket);
	return val;
}
