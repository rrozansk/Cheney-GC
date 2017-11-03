# Cheney-GC


[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green.svg)](https://github.com/rrozansk/Cheney-GC/blob/master/LICENSE.txt) [![RELEASE](https://img.shields.io/badge/release-v1-green.svg)](https://github.com/rrozansk/Cheney-GC/releases/tag/v1.0) [![BUILD](https://img.shields.io/badge/release-v2-yellow.svg)]()

An implementation of Cheney style garbage collection for use with cons cells.

A Makefile is included which can be used to generate an executable which will drive and help visualize the garbage collection process.
It constructs random trees, possibly cyclic, before triggering the garbage collector.
It prints out the trees, and optionally there memory addresses to show the objects moved but are still intact.
The printer/visualizer is also capable of handling cycles so these can also be viewed, since cheney garabge collection handles cycles naturally.

It is also possible to run the table driven tests automatically to make sure the implementation is compatable/works wth the choosen platform.
If all tests do not pass, or it exits abnormally the implementation is not compatable with your system.

NOTE: table driven tests are a work in progress, as well as making the heap expand dynamically if nothing is free'd after a collection.

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
$ make tar     # create a tarball out of the directory
$ make ctest   # compile and run the table driven tests, then clean
```
