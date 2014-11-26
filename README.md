/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */

Sandgrids

To run the simulation with OpenGL visualization:
`gcc -pthread -o renderpile render_piles.c sandgrid.c barrier.c -framework OpenGL -framework GLUT`



Test output for the code in `test.c`

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