Homework 08
===========
1. I first allocated enough memory for a single Entry struct by using calloc. I then allocated memory for the key of the newEntry by using strdup(key). Finally, I allocated memory for the value by using strdup(value..string). However, I only allocated this memory if type passed into the function was STRING. If not, this third allocation was not made.

I handeled the recursive flag in the delete function by using an if/else statement. If the flag was false, then the key of the entry was deallocated, the entry itself was deallocated, and the value was deallocated (only if the type was STRING). If the type was not STRING, then the value was not deallocated. If the recursive flag was true, thena  pointer was used to traverse the linked list. Every element of this list was freed accordinngly (free(key), free(entry), and only free(value) if value was of type STRING). 

2. I first allocated enough for a single Map struct by using calloc. I then made a Entry array and allocated memory for that. In order to allocate the correct ammount, calloc was used. This first argument passed in was newMap->capacity which lets calloc know how many of the second argument to allocate. Furthermore, the second argument was sizeof(Entry) so that an Enty spot was allocated as many times as the map's capacity. 

In map_delete I handled the internal entries by using a while loop. The condition used was while(bucketCounter+1 <= m->capacity). This made sure each bucket was cehcked. Then within this loop, entry_delete was called on the specific entry of the current bucket determined by the counter. entry_delete was caled with the recursive flag set to true, so that all entries in the linked list were deleted and not just the first one. After this while loop, m->buckets was freed, and finally the map itself, m, was freed.

3. In map resize, I allocated enough memory for a new array of entries. This was done by calloc(new_capacity, sizeof(Entry)). This consequently alocated enough memory for 'new_capacity' 'Entry' objects. I then copied the contents of the original array of entries into this new array. After this, the old array was deallocated. This fucntion is called when size/capacity is greater than the predetermined load_factor. Once this happens, the capacity of the map array is doubled. This function does this by first doubling the m->capacity value. After this, all the contents of the old array are put into the new array. However, in order to correctly do this, each element in the old array is given a new hash (since the capacity of the array changed). This new hash is used to places each entry from the old array into new spots in the new array. Essentially, thsi function completely rehashes the entire table.

4. Map insert works by first chekcing to see if the mapp needs to be resized by checking if size/capacity > load_factor. If this is the case then the map is resized. THis function then checks if the given key is already in the map. If it is, then this value in the map is replaced by the inserted value. If not, then the new value is inserted into the appropriate bucket at the front of the linked list. 

average time: constant to get to the appropriatte bucket, then it checks the linked list of that bucket (which is usually very small). So the overall average time is constant.

worse time: this happenes when the map is resized. THis effectively goes through the entire map so the time is O(n)

space: both are O(n)

5. map_search works by finding the has according to the key passed in. Then this hash is used to go to the correct bucket, and in that bucket the linked list is traveresed to finding the entry with the matching key. If not match is found, then NULL is returned

average time: O(1) constant
worse time: O(n) 

average and worse space: O(n)

6. map_remove works by first searching to see if the given key produces a map, if it does not, then false is returned. If there is a match then the key is used to go into the appropriatte bucket where a current and a previous pointer is used to traverse the linked list in that bucket. This is done so that once the match is found, the gap created by removing it can be fixed by setting prev->next to curr->next.

Average time: constant O(1)
worst time: O(n)

average and worse space: O(n)

Activity 2

1. As teh number of items increases, both time and space grow. As the load factor grows, space and time initially decrease. However, once a load factor of .9 is met, time starts to increase, but space continues to decrease.

This is not suprising, since the number of items was expected to make both increase. However, when it comes to the load fact it is kind of suprsing that once the load fact becomes greater than .9, the space continually decreases while the time increases.

2. Going off of the last sentence, this shoes the tradeofff for using a hash table. The space might become small with a high load_factor, but the time becomes greater and graeter. The advantage of a treap is that it never over allocates space for the entries. However, an advantage of using the hash table we developed is that searching, inserting, and deleteing are all constant time complexity algorithms. This allows for quick manipulations. I think I would use the hash table as an underlying data structure simply due to its speed. Hopefully the problem using the map has a size that can be estimated so that resizing does not need to happen all that often. However, if the size usage is unknown then a treap might be the better choice 
