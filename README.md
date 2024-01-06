# Stack Allocated Vector
> Visit the [wiki](https://github.com/KamilKrauze/StackVector/wiki) for more information

A very similar and easy replacement where required of <b>``std::vector<class T>``</b> data structure, the key difference being the data is dynicamically allocated on the stack, resulting in being cache-coherent.

Normally, for general use-cases dynamic stack allocation should be avoided as it may result code being unsafe.
However, some circumstances call for dynamic stack allocation and can be seen in areas where speed of execution is important such as real-time 3D renderers, raytracres, patch tracers or game engines, as some parts in memory may be read and written to multiple times and if it were allocated on the heap the time taken would be a lot longer comparitively to stack allocated memory.
