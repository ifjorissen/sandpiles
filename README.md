#Sandgrids
--------------

To compile everything:
`make`

To run OpenGL viz or ASCII vis:
`./renderOpenGL`
`./renderASCII`
 
##General Notes:

 `sandgrid.c` and `render_piles.c` are the master blocks of this program. Sandgrid.c runs what's necessary to generate the ASCII viz, and Render_piles.c for the OpenGl viz. 
 Both files make use of a global variable called gridsim (of type grid_simulation_t) which
 holds a pointer to the sandgrid, an array of pthreads, a pointer to the barrier, and an
 array of mutexes which are used in the locking mechanism for the grid regions. 
 The number of grains on the grid is defined in `header.h`, along with the number of threads in the program. 


##Grid stucture:

Example of how a 12x12 grid might be broken up with 4 threads

```

Compass: 
     N
   W . E
     S
    _________________________
    |*|S|I|N|K|*|C|E|L|L|S|*|
    |S|_|_|_|_|_|_|_|_|_|_|S|
    |I|_|_|_|_|_|_|_|_|_|_|I|----> rows 2/3 mutex 1
    |N|_|_|_|_|_|_|_|_|_|_|N|
    |K|_|_|_|_|_|_|_|_|_|_|K|
    |*|_|_|_|_|_|_|_|_|_|_|*|----> rows 5/6 mutex 2
    |C|_|_|_|_|_|_|_|_|_|_|C|
    |E|_|_|_|_|_|_|_|_|_|_|E|
    |L|_|_|_|_|_|_|_|_|_|_|L|----> rows 8/9 mutex 3
    |L|_|_|_|_|_|_|_|_|_|_|L|
    |S|_|_|_|_|_|_|_|_|_|_|S|
    |*|S|I|N|K|*|C|E|L|L|S|*|

```


##Todo:
* BUG: Hard to reproduce, but I will sometimes get an Illegal Hardware Instruction error
  e.g [1]    84998 illegal hardware instruction  ./renderASCII
* In stabilize function: thread waits if the mutex is locked? 
* Cells which are sinks and can hold any number of grains (Done)
* OpenGl animation


Test output for the code in sandpiles

```
	stabilize called from thread: 1
	stabilize called from thread: 0
	stabilize called from thread: 2
	stabilize called from thread: 3
	barrier wait called, capacity: 4
	barrier wait called, capacity: 4
	barrier wait called, capacity: 4
	barrier wait called, capacity: 4
	mutex locked
	waiting count = 1
	mutex locked
	waiting count = 2
	mutex locked
	waiting count = 3
	mutex locked
	condition met, mutex unlocked
```