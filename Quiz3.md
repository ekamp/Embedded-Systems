#Quiz 3 Study Guide

- Most data structures we norm deal with are optimized for speed, however we should also care about mem consumption and code size.
- <b>In Place</b> : Consumes a constant amount of space
- However we do want the algorithm to be reasonably fast

##Insertion Sort
- Runtime : O(n<sup>2</sup>) , &Omega(n)
- Very Fast on small inputs, has a small code size and is very simple

##Heap Sort
- Runtime : O(nlog(n))
- More complex than insertion sort
- Builds a heap of elements and then removes them one at a time (Heapify)

##Selection Sort
- Similar code but runs in &Theta(n<sup>2</sup>)

##Bubble Sort
- NEVER USE

##General Mem Usage
- If we have flash memory just sort it and write it back
- Little RAM : Give up speed for n swaps and at most 2n writes

##Hashes and Trees
- Use a hash to store things for cache memory such as IP addresses
    - However need a large array for this and collisions are very likely
- Can alternatively use a tree with O(nlog(n)) search time
- Alternitaively we can use a Bloom filter which will have a hash for each bit and k is present if all bits are set for it in each hash
- False pos can happen but false neg cannot because we can quickly tell if something is not in the hashes however sometimes it is possible that we id something as being in their that really is not

##Buffering
- Many time systems have real time tasks
- In order to take care of this data is read ahead of time and buffered

##Double Buffering
- Sometimes there is much latency or lag from a single buffer.
- Therefore we can read future data in one buffer while the other buffer is read by the system.
- Then when the first buffer has been read through completely the system reads from the other and the first reads future data

##Ring Buffer
- Like a circular linked list
- Has a head where the data is placed and a tail where the data is read
- When data gets inserted the head moves forward 
- When data is read tail moves forward
- When the tail reaches the head the buffer is then empty
