#Data Structures And Algorithms
- Most of the data structures are optimized for speed 
- Embedded systems often care ablut code size and memory consumption

##Space Efficient Sorting
- We want an in place algorithm
	- This means it consumes a constant amount of extra space
	- For instance a temp value for swapping things in memory
- What if we had a system with exremely slow memory?
	- load data into flash and sort it and write it back
- What if we have little RAM
	- How about selection sort?
	- Give up some speed for n swaps and at mose 2n writes

##Fast Set Matching
- Cache lookups are very commmon in embedded systems
	- Cacheing data means it doesnt need to be refetched
	- Example : router remembers malicious IP Addresses

##Sets with hashes and trees
- Use of a hash function to map from IP addresses to a cell in a larage array
- Check cell for IP address presence
- But now we need to keep a big array for the hash itself
- Sorted trees allow searching in O(log(n)) time
- But now we need to manage complex data structures

##Bloom Filter
- This is like a hash table buttt.
	- Uses multiple hashes instead of just one h<sub>1</sub>(k), h<sub>2</sub>(k)...
	- Sets a bit for each hash function
	- k is pressent if bits for all hashes are set
	- Only requires constant memory
- False positives possible but false negatives are not
	- In IP address example quickly see if the IP is safe
	- Use a second longer check to verify IP is in the cache

##Buffering
- Embedding systems often have real time tasks
- Reading from external memory is usually high-latency
- To overcome this mismatch data must be read ahead of time and buffered
- The simplest solution is called double buffering
- Everybody video card does this to prevent tearing
	- Software writes pixels for the next frame to Buffer A
	- Hardware bits pixels Buffer B onto the screen
	- Next round they swap : software writes to Buffer B's pixels hardware bits Buffer A's pixels

##Overcoming Greater Latency
- What if we need a deeper buffer?
	- Need some kind of queue but
		- Cant implement this efficiently with a growing vector or array
		- A list would require memory management using a ring buffer

##Ring buffer
- A ring buffer implements a conceptual circular data structure
- Uses a fixed size array for memory
