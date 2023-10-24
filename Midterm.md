# Midterm

## LEC0101 Storage

### SSD

* page: minimum R/W unit
* Erase unit: all date same time, lifetime

* Copy-on-write / out-of-space update: bitmap
* Garbage collection
  1. Find the EU with the least live data
  2. Copy live pages to an EU with free space
  3. Erase the target EU
* 7 principles for making most of SSD
  1. Avoid small updates: each time need to read & rewrite whole page
  2. Avoid random updates: write sequentially, at the same time and all at once
  3. Prioritize Reads over Writes: Writes take longer to execute than reads and
     may also entail write-amplification. This degrades SSD performance and lifetime.
  4. Reads/Writes should be page aligned
  5. Asynchronous I/Os for the win
  6. Defragmentation on SSDs is a Bad Idea
  7. Artificial Over-Provisioning

### Write-Amplification

* WA = physical work gets done within SSD / logical work trying to do
* Over-provision: SSD is assigned more physical space than the logical capacity it exposes to the user
* Quantifying WA = 1 + x / (1-x)
  * x: avg fraction of valid page in target EU
  * y: pages each EU
  * Invalid pages = (1-x) * y; migrate valid = x * y
  * migrate each invalid page = x * y / (1-x) * y = x / (1-x)
  * Write one page = migrate to free one + write one = 1 + x / (1-x)
* WA from user's perspective = B * (1 + x / (1-x))
  * the total amount of physical space within the SSD that gets rewritten divided by the size of the update that the user wanted to make.
  * B data items fit into each page and that the user updates one random entry in each request. If want to update one entry, we need to update one page
* Worst-case WA = B * (1 + (L/P) / (1 - (L/P))) = B * (1 + L / (P - L))
  * the logical capacity of the SSD as L and the physical capacity of the SSD as P
  * in each full erase unit, a fraction of L/P of the pages is valid while 1-L/P is invalid
* Uniformly random distributed WA = B * (1 + (L/P) / 2 * (1 - (L/P))) = B * (1 + L / 2 * (P - L))



## LEC0201 Tables Management

### DAM -- cost model

* N entries each table, B entries each page
* For simplicity, ignore:
  * Sequential reads
  * Asynchronous IOs
  * Garbage collections of random writes
* Scan
  * Cost: O(N/B) I/Os
  * Page belong to which table? 
    * Linked List: only support synchronous I/Os, not exploit ssd parallelism,
    * Directory: sequential problems, store in different locations, not exploit sequential bandwidth 
    * Multiple pages continuously
  * Keep track?
    * all
    * Free: linked list, bitmap
* Delete
  * Cost
    * Scan & delete: O(N/B) reads, O(1) write
* Update
  * Cost
    * Scan & update: O(N/B) reads, O(1) write
* Insert
  * Cost
    * Scan & insert: O(N/B) reads, O(1) write
    * Linked list record free space:
      * Fixed-size entries: No read, O(1) write
      * Variable-size entries: O(N/B) reads, O(1) write
    * Buffer read, flash to extent when reach one page: No reads, O(1/B) write

### Internal page organization

* One by one: need to reorganize for delete
* Bitmap at the beginning to record free page: no reorganize, need more space
* Variable length each row
  * Pointer on the top (fixed size): so the number of row could be recorded is fixed, if the data size of each row is small, the rest of this page could be wasted
  * Store from the end: provide the flexibility of how much rows to store
  *  How to store pointers?
    * Delimiter: traverse, no random access
    * Pointers of pointers: need more space
    * ![Screenshot 2023-10-23 at 19.08.01](/Users/yuyanting/Library/Application Support/typora-user-images/Screenshot 2023-10-23 at 19.08.01.png)



## LEC0202 Buffer Management

### Buffer Pool

Hot page

### Eviction policy

Evict entry in buffer pool when it is full

Two rules: keep frequently used page (eviction effectiveness); less cpu and extra metadata cost (cpu efficiency & memory)

Trade-off

* Random eviction: evict collided one
  * Pros: no hash collision algorithm needed => simple, cpu efficient, not extra metadata
  * Cons: may evict frequently used page
* FIFO
  * Reason: the older one is less likely to be used again
  * Implementation: queue, or array with front & rear pointers
  * Evict head pointer corresponding buffer pool block, move head pointer -> calculate # buffer -> deal with collision -> insert into queue, move rear pointer
  * Collision resolution algo
  * Problem: older one maybe frequently used
* LRU least recently used
  * reason
  * Implementation: double linked list => random access queue, with pointer pointing to buffer pool node
  * Evict front when full; insert to rear; access move to the rear
  * Problems
    * CPU overhead: update queue each access
    * Less efficient: double linked list pointer chasing, compared with array
    * Metadata overhead: pointers
* Clock
  * Traverse hash table circularly as a clock, evict not used since last traversal
  * Implementation: bitmap, init 0, used 0, each traversal evict 0 and change 1 to 0
  * Pros: no queue lower overhead (1,2); bitmap less extra space(3)
  * Cons: more likely evict hot page than LRU, better than FIFO





## LEC03 Indexing

Scanning one by one is not time-efficient when there are a few matching rows, O(N/B) I/Os

### Zone Maps

* Record min, max of each zone
* Worst case: O(N/B) I/Os when target is in the min, max range of all zones

### Sorted Files

Sort based on one column

* Scan: I/O O(log2(N/B)); CPU O(log2(N/B) + log2B)
* Insert/Update: binary search to find the target location, then insert, move rest of elements one slot (keep sorted), O(N/B)

### Binary Tree

Binary tree in storage, map each key to its page

* I/O: O(log2(N/B))
* CPU: O(log2N)

### Hash Table

* cost
* downsides

### Extendible Hashing

* A <u>directory</u> maps pages in storage with a given <u>hash prefix</u>

* Overflow with chaining
* Reach the capacity, double directory size => add one bit => new dir pointing to previous pages => split overflowing buckets to two
* Compare with Hash Table

### B-Tree

* B is max # of keys each node
* x keys, x+1 subtrees
* N/B leaves, storing index and its page #

 * cost
   * Search
     * I/Os: depth, O(logB(N/B)) = O(logB(N)) (B << N)
     * CPU: O(logBN * log2B) = O(log2N) comparison, logBN is # pages searched, log2B is binary search inside each page
   * Insert 
     * Full : split -> insert -> connect new node to parent -> create new parent -> split -> connect new parent to grandparent -> ...
     * I/O cost
       * Read: depth, O(logBN)
       * Write: O(1) = 1 + B-1 + B-2 + B-3 + …
         * Every insertion updates 1 leaf
         * one in O( B-1 ) insertions triggers leaf split
         * one in O( B-2 ) insertions triggers parent split
         * one in O( B-3 ) insertions triggers grandparent split
         * ...
   * Range scan (e.g. A > 25 and A < 35)
     * Search start -> iterate leaves until end
     * I/O Cost: O(logBN + S); S = # entries in the range, each entry one I/O since in diff pages
   * Clustered Index
     * Each leaf, storing index and data
     * Range scan I/O cost: O(logBN + S/B); data stored within index, S entries, S/B pages
     * Shortage: 

Downsides of indexing

* Extra space (take up storage space)
* Update index when data changes



## LEC04&05 LSM-Trees

### Basic LSM-Tree (T=2)

* Good insertion: buffering; good lookups: sort-merging SSTs

* Full -> sort-merge -> eliminate duplicates -> discard original arrays (flush) -> data in next level

* Update

  * Out-of-place, insert into buffer
  * The most recent version

* Delete

  * Insert a tombstion

* Query

  * Search from small to large level, return the first entry with matching key
  * Cost = O(log2(N/P) * logB(N))
    * \# levels = O(log2(N/P)), P is buffer size (\# entries)
    * search each level with binary search= O(log2(N/B)), B is page size (\# entries)
    * Struct each SST as B-tree, search each level = O(logB(N))

* Scan

  * mechanism

    1. Allocate an in-memory buffer (>1 page) for each level

    2. Search for start of key range at each level

       Loop until reaching end of range

       3. Output youngest version of entry with next smallest key
       4. If we traverse last entry in a given buffer, read next page from run

  * I/O Cost = O(log2(N/P) * logB(N) + S/B)

    * \# levels
    * B-tree search cost
    * output size

* Insert/Update/Delete

  * I/O Cost = O((log2(N/P))/B) each Read & Write
    * Times of copy of each entry: O(log2(N/P))
    * Cost of each copy: O(1/B) read & write

* B-trees in memory

  * No b-tree cost, delete all O(logB(N)) term
  * Memory cost = O(N/B)

### leveled LSM-tree

One block come, merge-sort inside level, 1 sorted block (len < T) inside each level

* Ratio size T, buffer size P
* Lookup cost = O(logT(N/P)) // \# levels
* Insertion cost = O(T/B * logT (N/P))
  * Each level T blocks, each entry need to be merged T times
  * \# levels
* T +, lookup cost -, insertion cost +
* When T = N/P, lookup cost = O(1), insertion cost = O(N/(B*P)) => sorted file



### tiered LSM-tree

Not merge inside level, merge-sort & flush to next level, <T separated sorted blocks inside each level

* Lookup cost = O(T * logT(N/P))
  * Search inside level
  * \# levels
* Insertion cost = O(1/B * logT(N/P))
* T +, lookup cost +, insertion cost -
* When T = N/P, lookup cost = O(N/P), insertion cost = O(1/B) => appended-only file

### bloom filters

* Bloom filters in memory, data in SSDs

* Insert: bitmap 0 -> 1
* Negative: not exist, at least one bit 0
* Positive: exist but may be wrong, all 1
  * True: real exist
  * False: not exist
* \# hash functions
  * 1, too few, false positive
  * Adding more hash functions, decrease false positive rate (FPR)
  * \# hash function = ln(2) * M  // M is # bits per entry
  * FPR = 2^(−M⋅ln(2))

* Cost
  * Insertion = M · ln(2) (# hash functions )
  * Positive query = M · ln(2) (# hash functions )
  * Avg negative query = 1 + 1/2 (1 + 1/2 · ( … )) = 1 + 1/2 + 1/4 + … = 2
  * Worst-case: fp, fp, ..., fp, tp; cost = O(M * L)  // L is \# levels
  * Avg worst case: neg, neg, ..., neg, tp = O(M + L)