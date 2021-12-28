# particle-sim

Particle gravity simulation built in C++. Forces between particles are approximated using the Octree data structure, which approximates a cluster of 'far particles' as one large particle.

## Requirements

```
- A C++ 14 Compiler
- CMake 3.17.3+ (probably works on some earlier versions of CMake 3.x)
- SDL2.
```

## Building
### Unix/Linux/OS X

In a terminal, cd to the project root directory and execute:

```
cmake -S . -B build
cmake --build build
```

to build the project. Any relatively recent C++ compiler should be able to build the output. To run the simulation execute:

```
bin/run_sim
```