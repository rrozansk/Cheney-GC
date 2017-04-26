# Cheney-GC

[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green.svg)](https://github.com/rrozansk/Cheney-GC/blob/master/LICENSE.txt) [![RELEASE](https://img.shields.io/badge/release-stable-green.svg)]()

An implementation of Cheney style garbage collection for use with cons cells. 

The repository includes three libraries:
  * bits - capable of bit manipulations on pointers
  * trees - binary tree generator/printer capable of handling cycles
  * cheney - garabge collector and cons cell implementations

A Makefile is also included along with test.c which generates an executable to drive and visualize the garbage collection process.

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
