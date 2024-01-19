# Stack Allocated Vector
> Visit the [wiki](https://github.com/KamilKrauze/StackVector/wiki) for more information

## Description
This is a header only library, so you can just download the header file and include it in your project (with the LICENSE naturally).
A very similar and easy replacement where required of <b>``std::vector<class T>``</b> data structure, the key difference being the data is dynicamically allocated on the stack, resulting in being cache-coherent.

Normally, for general use-cases dynamic stack allocation should be avoided as it may result code being unsafe and/or unstable due to the nature of dynamic stack allocation and other methods should be sought after.

However, some circumstances may call for dynamic stack allocation and can be seen in areas where speed of execution is important such as real-time 3D renderers, raytracres, patch tracers or game engines, as some parts in memory may be read and written to multiple times and if it were allocated on the heap the time taken would be a lot longer comparitively to stack allocated memory.

I wouldn't say this is the best solution out there, but this is my approach to it. The implementation is similar to that of the `std::vector` implementation, so it should be a general drop-in replace.

## Usage
1. If you want to use this library in your code then just include the `stack_vector.hpp` file located at `~/StackVector/include/`
2. To run tests go to the [Project Setup](#project-setup) section.

## Project Setup
> $${\color{yellow}You \space may \space use \space CMake \space or \space Premake \space to \space generate \space your \space project. }$$

### CMake
If you want to run the tests for yourself, download [CMake](https://cmake.org/) to your respective platform and then generate necessary project files.
You may use the CMake GUI if you find it easier over using the CLI. Just do `configure` then `generate`

Otherwise use the CLI at the project working directory like so:

> #### Configure
> > Windows
> > ```bat
> > cd build; cmake -G "Visual Studio 17 2022" ..; cd..
> > ```
>
> > Linux
> > ```bash
> > cd build; cmake -G "Unix Makefiles" ..; cd ..
> > ```
>
> #### Build
> > Debug
> > ```bat
> > cmake --build . --config Debug
> > ```
>
> > Release
> > ```bash
> > cmake --build . --config Release
> > ```
> <br>

### Premake
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
> I don't own a Mac and have never programmed on Mac, so fend for yourselves.

More information can be found [here](https://premake.github.io/docs/Using-Premake/#using-premake-to-generate-project-files).
