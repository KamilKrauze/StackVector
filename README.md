# Stack Allocated Vector
> Visit the [wiki](https://github.com/KamilKrauze/StackVector/wiki) for more information

## Description
A very similar and easy replacement where required of <b>``std::vector<class T>``</b> data structure, the key difference being the data is dynicamically allocated on the stack, resulting in being cache-coherent.

Normally, for general use-cases dynamic stack allocation should be avoided as it may result code being unsafe.
However, some circumstances call for dynamic stack allocation and can be seen in areas where speed of execution is important such as real-time 3D renderers, raytracres, patch tracers or game engines, as some parts in memory may be read and written to multiple times and if it were allocated on the heap the time taken would be a lot longer comparitively to stack allocated memory.

## Setup
This is a header only library, so you can just download the header file and include it in your project (with the LICENSE naturally).

If you want to run the tests for yourself, download [Premake5](https://premake.github.io/) to your respective platform and then generate necessary project files.
This is platform dependent so here is a quick guide:
> Windows
> ```bat
> ./premake5 vs2022
> ```

> Linux
> ```bash
> ./premake5 gmake2
> ```

> MacOS
> 
> I don't own a Mac and have never programmed on Mac, fend for yourselves.

More information can be found [here](https://premake.github.io/docs/Using-Premake/#using-premake-to-generate-project-files).
