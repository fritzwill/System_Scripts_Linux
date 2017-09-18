/* map.c: separate chaining hash table */

#include "map.h"

/**
 * Create map data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @param   load_factor     Maximum load factor before resizing.
 * @return  Allocated Map structure.
 */
Map *	        map_create(size_t capacity, double load_factor) {
    //printf("create\n");
    if (capacity == 0) capacity = DEFAULT_CAPACITY;
    if (load_factor <= 0) load_factor = DEFAULT_LOAD_FACTOR;
    Map * newMap = calloc(1, sizeof(Map));
    if (newMap == NULL){ // checks if allocation fails
        return NULL;
    }
    newMap->capacity = capacity;
    newMap->load_factor = load_factor;
    newMap->size = 0;
    Entry * arrayBuckets = calloc(newMap->capacity, sizeof(Entry));
    newMap->buckets = arrayBuckets;
    return newMap;
}

/**
 * Delete map data structure.
 * @param   m               Map data structure.
 * @return  NULL.
 */
Map *	        map_delete(Map *m) {
    uint64_t bucketCounter = 0;
    while (bucketCounter+1 <= m->capacity){
        //printf("1:enter\n");
        entry_delete(m->buckets[bucketCounter].next, true);
        bucketCounter++;
    }
    //printf("1:exit\n");
    free(m->buckets);
    free(m);
    return NULL;
}

/**
 * Insert or update entry into map data structure.
 * @param   m               Map data structure.
 * @param   key             Entry's key.
 * @param   value           Entry's value.
 * @param   type            Entry's value's type.
 */
void            map_insert(Map *m, const char *key, const Value value, Type type) { 
    bool newEntry = true;
    double loadCheck = m->size/(double)m->capacity;
    if (loadCheck > m->load_factor) {
        map_resize(m, 2*(m->capacity));
    }
    uint64_t bucket = fnv_hash(key, strlen(key));
    bucket = bucket % m->capacity;
    Entry * helper = m->buckets[bucket].next;
    while (helper != NULL){
        //printf("2:enter\n");
        if (strcmp(helper->key, key) == 0){
            entry_update(helper, value, type);
            newEntry = false;
            break;
        }
        helper = helper->next;
    }
    //printf("2:exit\n");
    if (newEntry) {
        m->size = m->size + 1;
        m->buckets[bucket].next = entry_create(key, value, m->buckets[bucket].next, type);
    }
}

/**
 * Search map data structure by key.
 * @param   m               Map data structure.
 * @param   key             Key of the entry to search for.
 * @param   Pointer to the entry with the specified key (or NULL if not found).
 */
Entry *         map_search(Map *m, const char *key) {
    uint64_t bucket = fnv_hash(key, strlen(key));
    bucket = bucket % m->capacity;
    Entry * ptr = m->buckets[bucket].next;
    while (ptr != NULL){
        //printf("3:enter\n");
        if (strcmp(ptr->key, key) == 0) return ptr;
        ptr = ptr->next;
    }
    //printf("3:exit\n");
    return NULL;
}

/**
 * Remove entry from map data structure with specified key.
 * @param   m               Map data structure.
 * @param   key             Key of the entry to remove.
 * return   Whether or not the removal was successful.
 */
bool            map_remove(Map *m, const char *key) {
    Entry * match = map_search(m, key);
    if (match == NULL) return false;
    uint64_t bucket = fnv_hash(key, strlen(key));
    bucket = bucket % m->capacity;
    Entry * curr = m->buckets[bucket].next;
    Entry * prev = &m->buckets[bucket];
    while (curr != NULL) {
        //printf("4:enter\n");
        if (strcmp(curr->key, key) == 0) {
            prev->next = curr->next; 
            entry_delete(curr, false);
            m->size = m->size - 1;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    //printf("4:exit\n");
    return false;
}

/**
 * Dump all the entries in the map data structure.
 * @param   m               Map data structure.
 * @param   stream          File stream to write to.
 * @param   mode            Dump mode to use.
 */
void		map_dump(Map *m, FILE *stream, const DumpMode mode) {
    uint64_t bucketCounter = 0;
    Entry * ptr = NULL;
    while (bucketCounter+1 <= m->capacity){
        ptr = m->buckets[bucketCounter].next;
        while (ptr != NULL){
            //printf("5:enter\n");
            entry_dump(ptr, stream, mode);
            ptr = ptr->next;
        }
        //printf("5:exit\n");
        bucketCounter++;
    }
}

/**
 * Resize the map data structure.
 * @param   m               Map data structure.
 * @param   new_capacity    New capacity for the map data structure.
 */
void            map_resize(Map *m, size_t new_capacity) {
    Entry * newBuckets = calloc(new_capacity, sizeof(Entry));
    uint64_t bucketCounter = 0;
    uint64_t bucket;
    Entry * ptr;
    Entry * next;
    while (bucketCounter+1 <= m->capacity){
        //printf("6:enter\n");
        ptr = m->buckets[bucketCounter].next;
        while (ptr != NULL){
            //printf("7:enter\n");
            bucket = fnv_hash(ptr->key, strlen(ptr->key));
            bucket = bucket % new_capacity;
            next = ptr->next;
            ptr->next = newBuckets[bucket].next;
            newBuckets[bucket].next = ptr; 
            ptr = next;
        }
        //printf("7:exit\n");
        bucketCounter++;
    }
    //printf("6:exit\n");
    free(m->buckets);
    m->buckets = newBuckets;
    m->capacity = new_capacity;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
