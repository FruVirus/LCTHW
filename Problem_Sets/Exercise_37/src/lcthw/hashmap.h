#ifndef _lcthw_Hashmap_h
#define _lcthw_Hashmap_h

#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUMBER_OF_BUCKETS   (100)

// This is a comparison function that the Hashmap uses to find elements by their key.
typedef int (*Hashmap_compare)(void *a,void *b);

// This is the hashing function and it's responsible for taking a key, processing its contents, and producing
// a single 'uint32_t' index number.
typedef uint32_t (*Hashmap_hash)(void *key);

// 'DArray *buckets' is a dynamic array that will be set to a fixed size of 'DEFUALT_NUMBER_OF_BUCKETS'.
// Each bucket will in turn contain a 'DArray' that will hold 'HashmapNode' pairs.
typedef struct Hashmap
{
    DArray *buckets;
    Hashmap_compare compare;
    Hashmap_hash hash;
} Hashmap;

// Each 'HashmapNode' holds a key/value pair along with the unique hash value.
typedef struct HashmapNode
{
    void *key;
    void *data;
    uint32_t hash;
} HashmapNode;

typedef int (*Hashmap_traverse_cb)(HashmapNode *node);

// This function creates a 'Hashmap' pointer.
Hashmap * Hashmap_create(Hashmap_compare compare,Hashmap_hash hash);

// This function sets a key/value pair in 'map'.
int Hashmap_set(Hashmap *map,void *key,void *data);

// This function returns the value corresponding to 'key' in 'map'.
void * Hashmap_get(Hashmap *map,void *key);

// This function traverses through all the nodes in 'map->buckets'.
int Hashmap_traverse(Hashmap *map,Hashmap_traverse_cb traverse_cb);

// This function deletes a key/vale pair.
void * Hashmap_delete(Hashmap *map,void *key);

// This function destroys a 'Hashmap' pointer.
void Hashmap_destroy(Hashmap *map);

#endif
