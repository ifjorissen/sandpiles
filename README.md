#Sandgrids
--------------

github repository [https://github.com/ifjorissen/sandpiles]

To compile everything:
`make`

To run OpenGL viz or ASCII vis:
`./renderOpenGL`
`./renderASCII`
`./speedTest`
 
##General Notes:

 `sandgrid.c`, 'timedGrid.c' and `render_piles.c` are the master blocks of this program. Sandgrid.c runs what's necessary to generate the ASCII viz, and Render_piles.c for the OpenGl viz.
 TimedGrid.c runs the sandpiles stabilization with varying grain amounts and thread numbers. 
 All three files make use of a global variable called gridsim (of type grid_simulation_t) which
 holds a pointer to the sandgrid, an array of pthreads, a pointer to the barrier, and an
 array of mutexes which are used in the locking mechanism for the grid regions. It also holds an integer with
 the number of total threads working on the grid as well as an integer variable indicating the stability of the grid and (a mutex to protect it). 
 


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
* In stabilize function: thread waits if the mutex is locked? 
* OpenGl animation


###Sample RESULTS section output from timedGrid.c

```
RESULTS:
Stabilizing a 64x64 grid with 100 grains and 1 threads took: 0.001490 seconds
Stabilizing a 64x64 grid with 100 grains and 2 threads took: 0.001859 seconds
Stabilizing a 64x64 grid with 100 grains and 4 threads took: 0.008990 seconds
Stabilizing a 64x64 grid with 100 grains and 8 threads took: 0.029723 seconds
Stabilizing a 64x64 grid with 100 grains and 16 threads took: 0.112257 seconds

Stabilizing a 64x64 grid with 500 grains and 1 threads took: 0.006938 seconds
Stabilizing a 64x64 grid with 500 grains and 2 threads took: 0.015013 seconds
Stabilizing a 64x64 grid with 500 grains and 4 threads took: 0.066797 seconds
Stabilizing a 64x64 grid with 500 grains and 8 threads took: 0.122904 seconds
Stabilizing a 64x64 grid with 500 grains and 16 threads took: 0.518300 seconds

Stabilizing a 64x64 grid with 1000 grains and 1 threads took: 0.014778 seconds
Stabilizing a 64x64 grid with 1000 grains and 2 threads took: 0.022982 seconds
Stabilizing a 64x64 grid with 1000 grains and 4 threads took: 0.176954 seconds
Stabilizing a 64x64 grid with 1000 grains and 8 threads took: 0.332715 seconds
Stabilizing a 64x64 grid with 1000 grains and 16 threads took: 0.770323 seconds

Stabilizing a 64x64 grid with 2500 grains and 1 threads took: 0.043737 seconds
Stabilizing a 64x64 grid with 2500 grains and 2 threads took: 0.065450 seconds
Stabilizing a 64x64 grid with 2500 grains and 4 threads took: 0.405754 seconds
Stabilizing a 64x64 grid with 2500 grains and 8 threads took: 0.797659 seconds
Stabilizing a 64x64 grid with 2500 grains and 16 threads took: 2.474893 seconds

Stabilizing a 64x64 grid with 5000 grains and 1 threads took: 0.104062 seconds
Stabilizing a 64x64 grid with 5000 grains and 2 threads took: 0.140405 seconds
Stabilizing a 64x64 grid with 5000 grains and 4 threads took: 0.928000 seconds
Stabilizing a 64x64 grid with 5000 grains and 8 threads took: 1.788156 seconds
Stabilizing a 64x64 grid with 5000 grains and 16 threads took: 4.735727 seconds
```

###Sample output from a 16x16 grid with 100 grains of sand (verbose):
```
creating pthread 0
creating pthread 1
stabilize called from thread: 0. region lower bound: 0, region upper bound: 3
creating pthread 2
stabilize called from thread: 1. region lower bound: 4, region upper bound: 7
end of stabilize from thread: 0
creating pthread 3
joining pthread 0
stabilize called from thread: 2. region lower bound: 8, region upper bound: 11
end of stabilize from thread: 1
stabilize called from thread: 3. region lower bound: 12, region upper bound: 15
end of stabilize from thread: 2
end of stabilize from thread: 3
barrier met

iteration: 1
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 1 | 0 | 4 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 2 | 4 | 69 | 4 | 2 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 3 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
barrier met
stable: 4 tid: 0
stabilize called from thread: 0. region lower bound: 0, region upper bound: 3
stable: 4 tid: 3
stable: 4 tid: 1
stable: 4 tid: 2
end of stabilize from thread: 0
stabilize called from thread: 3. region lower bound: 12, region upper bound: 15
stabilize called from thread: 1. region lower bound: 4, region upper bound: 7
stabilize called from thread: 2. region lower bound: 8, region upper bound: 11
end of stabilize from thread: 3
end of stabilize from thread: 1
end of stabilize from thread: 2
barrier met

iteration: 2
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 3 | 2 | 4 | 1 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 3 | 4 | 2 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 1 | 3 | 2 | 45 | 4 | 0 | 2 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 1 | 0 | 3 | 0 | 3 | 1 | 1 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 2 | 1 | 1 | 1 | 2 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
barrier met
stable: 4 tid: 0
stable: 4 tid: 2
stable: 4 tid: 1
stabilize called from thread: 0. region lower bound: 0, region upper bound: 3
stable: 4 tid: 3
stabilize called from thread: 2. region lower bound: 8, region upper bound: 11
stabilize called from thread: 1. region lower bound: 4, region upper bound: 7
stabilize called from thread: 3. region lower bound: 12, region upper bound: 15
end of stabilize from thread: 0
end of stabilize from thread: 3
end of stabilize from thread: 2
end of stabilize from thread: 1
barrier met

iteration: 3
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 3 | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 2 | 4 | 1 | 2 | 0 | 1 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 1 | 3 | 2 | 4 | 1 | 2 | 2 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 2 | 4 | 1 | 20 | 0 | 2 | 3 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 1 | 2 | 5 | 5 | 2 | 4 | 1 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 2 | 2 | 3 | 3 | 2 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
barrier met
stable: 7 tid: 0
stabilize called from thread: 0. region lower bound: 0, region upper bound: 3
stable: 7 tid: 1
stable: 7 tid: 3
stable: 7 tid: 2
stabilize called from thread: 1. region lower bound: 4, region upper bound: 7
end of stabilize from thread: 0
stabilize called from thread: 3. region lower bound: 12, region upper bound: 15
stabilize called from thread: 2. region lower bound: 8, region upper bound: 11
end of stabilize from thread: 1
end of stabilize from thread: 3
end of stabilize from thread: 2
barrier met

iteration: 4
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 2 | 0 | 3 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 1 | 1 | 2 | 0 | 2 | 1 | 1 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 2 | 3 | 2 | 3 | 2 | 3 | 2 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 3 | 4 | 5 | 6 | 5 | 4 | 3 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 2 | 3 | 2 | 3 | 2 | 3 | 2 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 1 | 1 | 2 | 0 | 2 | 1 | 1 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 2 | 0 | 3 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
barrier met
stable: 5 tid: 0
stable: 5 tid: 2
stable: 5 tid: 1
stabilize called from thread: 0. region lower bound: 0, region upper bound: 3
stable: 5 tid: 3
stabilize called from thread: 2. region lower bound: 8, region upper bound: 11
stabilize called from thread: 1. region lower bound: 4, region upper bound: 7
stabilize called from thread: 3. region lower bound: 12, region upper bound: 15
end of stabilize from thread: 0
end of stabilize from thread: 1
end of stabilize from thread: 2
end of stabilize from thread: 3
barrier met

iteration: 5
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 2 | 0 | 3 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 2 | 2 | 3 | 1 | 3 | 2 | 2 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 1 | 0 | 3 | 2 | 3 | 2 | 3 | 0 | 1 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 1 | 3 | 1 | 3 | 4 | 3 | 1 | 3 | 1 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 1 | 0 | 3 | 2 | 3 | 2 | 3 | 0 | 1 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 2 | 2 | 3 | 1 | 3 | 2 | 2 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 2 | 0 | 3 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
barrier met
stable: 1 tid: 0
stabilize called from thread: 0. region lower bound: 0, region upper bound: 3
stable: 1 tid: 3
stable: 1 tid: 2
stable: 1 tid: 1
stabilize called from thread: 3. region lower bound: 12, region upper bound: 15
end of stabilize from thread: 0
stabilize called from thread: 1. region lower bound: 4, region upper bound: 7
stabilize called from thread: 2. region lower bound: 8, region upper bound: 11
end of stabilize from thread: 3
end of stabilize from thread: 1
end of stabilize from thread: 2
barrier met

iteration: 6
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 3 | 2 | 0 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 3 | 0 | 3 | 2 | 3 | 0 | 3 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 1 | 2 | 3 | 0 | 3 | 0 | 3 | 2 | 1 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 2 | 0 | 2 | 3 | 0 | 3 | 2 | 0 | 2 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 1 | 2 | 3 | 0 | 3 | 0 | 3 | 2 | 1 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 3 | 0 | 3 | 2 | 3 | 0 | 3 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 3 | 2 | 0 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 
the grid is stable
joining pthread 1
joining pthread 2
joining pthread 3
```



###Test output for the code in sandpiles

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