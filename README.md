# Cheney-GC

[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green.svg)](https://github.com/rrozansk/Cheney-GC/blob/master/LICENSE.txt) [![RELEASE](https://img.shields.io/badge/release-v1-green.svg)](https://github.com/rrozansk/Cheney-GC/releases/tag/v1.0) [![BUILD](https://img.shields.io/badge/release-v2-yellow.svg)]()

An [implementation](https://github.com/rrozansk/Cheney-GC/blob/master/src/cheney.c) of Cheney style garbage collection allowing allocation of cons cells which can store pointers to any arbitrary data. Additionally, the heap has been encapsulated into an structure allowing multiple garbage collected heaps to exist simultaneously, and if permitted they may also expand dynamically upon a collection which fails in reclaiming any memory. For a more thorough explanation of the libraries capabilities and exposed API see the [documentation](https://github.com/rrozansk/Cheney-GC/blob/master/include/cheney.h#L6).

A Makefile is also included which may be used to generate a simple repl (read evaluation print loop) with allows the dynamic interaction and exploration of the API's exposed by the library.

Finally, It is also possible to run the table driven [tests](https://github.com/rrozansk/Cheney-GC/blob/master/test/testCHENEY.c) automatically. Again, this is with the help of the Makefile. If all tests do not pass, or the program exits abnormally for any reason, then the implementation is not compatible with the system.

## Prerequisites
- gcc (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3 or equivalent
- make

## Getting Started
```sh
$ git clone https://github.com/rrozansk/Cheney-GC.git
$ cd Cheney-GC
$ make
$ ./cheney
```

## Makefile Commands
```sh
$ make         # compile the visual driver
$ make all
$ make build
$ make cheney
$ make clean   # remove all compiled files, executables, etc.
$ make rebuild # clean and recompile the visual driver
$ make install # rebuild and then copy executable to /usr/bin
$ make tar     # create a tarball out of the base directory
$ make ctest   # compile and run the table driven tests, then clean
```
