#undef NDEBUG
#include <stdint.h>
#include <lcthw/hashmap.h>
#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>
#include <inttypes.h>

// Basic C string comparison function.
static int default_compare(void *a,void *b)
{
    return bstrcmp((bstring)a,(bstring)b);
}

// Simple Bob Jenkin's hash algorithm taken from the Wikipedia description.
// Generates a unique hash value for each character in 'a'.
static uint32_t default_hash(void *a)
{
    size_t len = blength((bstring)a);
    char *key = bdata((bstring)a);
    uint32_t hash = 0;
    uint32_t i = 0;

    for (hash = i = 0;i < len;++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/*
 * 'map->buckets' is a DArray whose contents are individual buckets that are themselves DArrays.
 * For example, with 100 buckets, the values 0,10,20,...,90 will get set to bucket 0, the values
 * 1,11,21,...,91 will get set to bucket 1 and so on.
 *
 * Each element in 'map->buckets->contents' is a pointer to a single bucket (i.e., a DArray).
 * 'map->buckets' has:
 *      map->buckets->max: DEFAULT_NUMBER_OF_BUCKETS
 *      map->buckets->end: DEFAULT_NUMBER_OF_BUCKETS
 *      map->buckets->contents: DEFAULT_NUMBER_OF_BUCKETS void * pointers
 *      map->buckets->element_size: sizeof(DArray *) (i.e., 8 bytes)
 *      map->buckets->expand_rate: DEFAULT_EXPAND_RATE
 *
 * Automatically sets the 'end' index of 'map->buckets' to 'DEFAULT_NUMBER_OF_BUCKETS'
 * since this value is fixed.
*/
Hashmap * Hashmap_create(Hashmap_compare compare,Hashmap_hash hash)
{
    Hashmap *map = calloc(1,sizeof(Hashmap));
    check_mem(map);

    map->compare = compare == NULL ? default_compare : compare;
    map->hash = hash == NULL ? default_hash : hash;
    map->buckets = DArray_create(sizeof(DArray *),DEFAULT_NUMBER_OF_BUCKETS);
    map->buckets->end = map->buckets->max;
    check_mem(map->buckets);

    return map;

error:
    if (map)
        Hashmap_destroy(map);

    return NULL;
}

void Hashmap_destroy(Hashmap *map)
{
    int i = 0;
    int j = 0;

    if (map)
    {
        if (map->buckets)
        {
            for (i = 0;i < DArray_count(map->buckets);i++)
            {
                DArray *bucket = DArray_get(map->buckets,i);

                if (bucket)
                {
                    for (j = 0;j < DArray_count(bucket);j++)
                        // Free the individual elements within each bucket.
                        free(DArray_get(bucket,j));

                    // Free the bucket.
                    DArray_destroy(bucket);
                }
            }

            // Free the overall buckets pointer.
            DArray_destroy(map->buckets);
        }

        // Free the Hashmap pointer.
        free(map);
    }
}

static inline DArray * Hashmap_find_bucket(Hashmap *map,void *key,int create,uint32_t *hash_out)
{
    // Obtain the hash for the key.
    uint32_t hash = map->hash(key);

    // Assign a bucket to the hash that is within 'DEFAULT_NUMBER_OF_BUCKETS'.
    int bucket_n = hash%DEFAULT_NUMBER_OF_BUCKETS;
    check(bucket_n >= 0 && bucket_n < DEFAULT_NUMBER_OF_BUCKETS,"Invalid bucket found: %d",bucket_n);
    //printf("Hash: %" PRIu32 ", Bucket #: %d\n",hash,bucket_n);

    // Store the hash value for the return call so the caller can use it.
    *hash_out = hash;

    // Obtain the contents of 'map->buckets->contents[bucket_n]'.
    DArray *bucket = DArray_get(map->buckets,bucket_n);
    //printf("Content of 'map->buckets' in bucket: %d is: %s\n",bucket_n,bucket);

    /*
     * If there is nothing inside the bucket yet, create the bucket and set it in the correct position in
     * 'map->buckets->contents'.
     * Each element of the bucket is a void * pointer since it can be anything.
     *
     * 'bucket' has:
     *      bucket->max: DEFAULT_NUMBER_OF_BUCKETS
     *      bucket->end: 0;
     *      bucket->element_size: sizeof(void *) (i.e., 8 bytes)
     *      bucket->expand_rate: DEFAULT_EXPAND_RATE
     *      bucket->contents: 100 void * pointers
    */
    if (!bucket && create)
    {
        bucket = DArray_create(sizeof(void *),DEFAULT_NUMBER_OF_BUCKETS);
        check_mem(bucket);
        DArray_set(map->buckets,bucket_n,bucket);
    }

    return bucket;

error:
    return NULL;
}

static inline HashmapNode * Hashmap_node_create(int hash,void *key,void *data)
{
    HashmapNode *node = calloc(1,sizeof(HashmapNode));
    check_mem(node);

    node->key = key;
    node->data = data;
    node->hash = hash;

    return node;

error:
    return NULL;
}

int Hashmap_set(Hashmap *map,void *key,void *data)
{
    // Find the bucket that corresponds to 'key'. If the bucket doesn't exist, create it.
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map,key,1,&hash);
    check(bucket,"Error: Can't create bucket.");

    // After the bucket is found/created, create a hashmap node for the key/value pair.
    HashmapNode *node = Hashmap_node_create(hash,key,data);
    check_mem(node);

    // After the hashmap node is created for the key/value pair, add the node to the end of the
    // bucket. The bucket is automatically expanded to take in new values if necessary.
    DArray_push(bucket,node);
    //printf("Inside 'Hashmap_set': %d\n",hash%DEFAULT_NUMBER_OF_BUCKETS);
    //DArray *temp_bucket = map->buckets->contents[hash%DEFAULT_NUMBER_OF_BUCKETS];
    //HashmapNode *temp_node = temp_bucket->contents[0];
    //printf("%s\n",((bstring)temp_node->data)->data);

    return 0;

error:
    return -1;
}

static inline int Hashmap_get_node(Hashmap *map,uint32_t hash,DArray *bucket,void *key)
{
    int i = 0;

    for (i = 0;i < DArray_end(bucket);i++)
    {
        debug("TRY: %d",i);

        HashmapNode *node = DArray_get(bucket,i);

        if (node->hash == hash && map->compare(node->key,key) == 0)
            return i;
    }

    return -1;
}

void * Hashmap_get(Hashmap *map,void *key)
{
    // Find the bucket corresponding to the key.
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map,key,0,&hash);

    if (!bucket)
        return NULL;

    // Find the node within the bucket that contains the key/value pair.
    int i = Hashmap_get_node(map,hash,bucket,key);
    //printf("Inside 'Hashmap_get': %d\n",i);
    if (i == -1)
        return NULL;

    // After the node is found, obtain the contents of the node and return the value
    // corresponding to the key.
    HashmapNode *node = DArray_get(bucket,i);
    check(node != NULL,"Failed to get node from bucket when it should exist.");
    //printf("%s\n",((bstring)node->data)->data);

    return node->data;

error:
    return NULL;
}

int Hashmap_traverse(Hashmap *map,Hashmap_traverse_cb traverse_cb)
{
    int i = 0;
    int j = 0;
    int rc = 0;

    // Loop over the all the buckets in 'map->buckets'.
    for (i = 0;i < DArray_count(map->buckets);i++)
    {
        // Obtain an individual bucket.
        DArray *bucket = DArray_get(map->buckets,i);

        if (bucket)
        {
            // Loop over all the nodes in an individual bucket.
            for (j = 0;j < DArray_count(bucket);j++)
            {
                // Obtain the hashmap node.
                HashmapNode *node = DArray_get(bucket,j);
                rc = traverse_cb(node);

                if (rc != 0)
                    return rc;
            }
        }
    }

    return 0;
}

void * Hashmap_delete(Hashmap *map,void *key)
{
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map,key,0,&hash);

    if (!bucket)
        return NULL;

    int i = Hashmap_get_node(map,hash,bucket,key);

    if (i == -1)
        return NULL;

    HashmapNode *node = DArray_get(bucket,i);
    void *data = node->data;
    //printf("Hey! %s\n",((bstring)node->data)->data);
    free(node);
    //printf("Hey! %s\n",((bstring)node->data)->data);
    HashmapNode *ending = DArray_pop(bucket);

    // Swap the last node in the bucket with the node that was just freed.
    // Note: This step is necessary since freeing the node doesn't guarantee that it's contents are NULL.
    if (ending != node)
    {
        printf("%s\n",((bstring)ending->data)->data);
        DArray_set(bucket,i,ending);
        printf("%s\n",((bstring)ending->data)->data);
    }

    return data;
}
