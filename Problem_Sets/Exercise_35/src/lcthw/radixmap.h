#ifndef _radixmap_h

#include <stdint.h>

typedef union RMElement
{
    uint64_t raw;
    
    struct
    {
        uint32_t key;
        uint32_t value;
    } data;

} RMElement;

typedef struct RadixMap
{
    size_t max;
    size_t end;
    uint32_t counter;
    RMElement *contents;
    RMElement *temp;
} RadixMap;

// This function creates a 'RadixMap' pointer.
RadixMap * RadixMap_create(size_t max);

// This function destroys a 'RadixMap'pointer.
void RadixMap_destroy(RadixMap *map);

void RadixMap_sort(RadixMap *map);

RMElement * RadixMap_find(RadixMap *map,uint32_t key);

// This function adds a (key,value) pair to 'map->contents' at the end and then calls 'RadixMap_sort'.
int RadixMap_add(RadixMap *map,uint32_t key,uint32_t value);

int RadixMap_delete(RadixMap *map,RMElement *el);

#endif
