/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */

Sandgrids

To compile everything:
`make`

To run OpenGL viz or ASCII vis:
`./renderOpenGL`
`./renderASCII`


Todo:
* BUG: Hard to reproduce, but I will sometimes get an Illegal Hardware Instruction error
* In stabilize function: thread waits if the mutex is locked
* Cells which are sinks and can hold any number of grains
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



  * sandpile simulation
    * celluar automata that can be generalized to any graph
    * n x n sandpile grid
    if number of threads = 4; 

Compass: 
     N
   W . E
     S
    _________________________
    |_|_|_|_|_|_|_|_|_|_|_|_|
    |_|_|_|_|_|_|_|_|_|_|_|_|
    |_|_|_|_|_|_|_|_|_|_|_|_|----> rows 2/3 mutex 1
    |_|_|_|_|_|_|_|_|_|_|_|_|
    |_|_|_|_|_|_|_|_|_|_|_|_|
    |_|_|_|_|_|_|_|_|_|_|_|_|----> rows 5/6 mutex 2
    |_|_|_|_|_|_|_|_|_|_|_|_|
    |_|_|_|_|_|_|_|_|_|_|_|_|
    |_|_|_|_|_|_|_|_|_|_|_|_|----> rows 8/9 mutex 3
    |_|_|_|_|_|_|_|_|_|_|_|_|
    |_|_|_|_|_|_|_|_|_|_|_|_|
    |_|_|_|_|_|_|_|_|_|_|_|_|