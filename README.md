# Cheney-GC

[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green.svg)](https://github.com/rrozansk/Cheney-GC/blob/master/LICENSE.txt) [![RELEASES](https://img.shields.io/badge/Releases-current-green.svg)](https://github.com/rrozansk/Cheney-GC/releases)

An [implementation](https://github.com/rrozansk/Cheney-GC/blob/master/src/cheney.c#L1) of [Cheney](https://en.wikipedia.org/wiki/Cheney%27s_algorithm) style garbage collection allowing the allocation of [cons cells](https://en.wikipedia.org/wiki/Cons). These cells are capable of storing pointers to other cells or atomic data (represented as a [tagged pointer](https://en.wikipedia.org/wiki/Tagged_pointer) or NULL). This allows the storage of any other data type's pointer or even possibly encoding the information itself directly into a pointer.

Furthermore, the heap has been encapsulated into a structure allowing multiple garbage collected heaps to exist simultaneously. Ultimately, this allows clean interaction through a well defined API. However, this could be useful for other reasons, one of which may be to maintain different memory pools if computing on threads. It is also possible, if permitted, for the heap to expand dynamically. Dynamic expansion can only happen when a collection fails in reclaiming memory or through the exposed 'resize' API call. For a more thorough explanation of all the libraries capabilities and exposed API's see the [documentation](https://github.com/rrozansk/Cheney-GC/blob/master/include/cheney.h#L6).

Finally, table driven testing is deployed to ensure correctness and compatability while allowing expansion of test cases with minimal effort. A Makefile is included to help automate and run the [test suite](https://github.com/rrozansk/Cheney-GC/blob/master/test/cheney.c#L6) using the commands listed below. If any test fails or the program exits abnormally then the implementation is not compatible with the choosen system. Following the link above will lead you to directions for adding your own tests to the suite if so desired.

## Prerequisites
- gcc (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3 or equivalent C compiler
- make

## Getting Started
```sh
$ git clone https://github.com/rrozansk/Cheney-GC.git
$ cd Cheney-GC
$ make tests
```

## Makefile Commands
```sh
$ make         # compile and execute the table driven tests, then cleanup
$ make all
$ make build
$ make tests
$ make clean   # remove all compiled and tmp files as well as the executable
$ make rebuild # clean and build
$ make tar     # create a tarball containing the core files of the project
```
