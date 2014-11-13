metaii
======

Exploration of Val Schorre's META II.

## Files
schorre-metaii.meta  META II definition from the paper (except in lowercase).
schorre-metaii.vm    Hand-compiled version to the VM defined in the paper.
metaii.meta          A version on META II that compiles to C++. Only defines enough to self-compile.
metaii.h             META II run-time.
metaii.cpp           Machine compiled version of metaii.meta.

## Build
Tested with GCC 4.8.3:

  g++ -I. -O3 --whole-program metaii.cpp -o metaii
  ./metaii < metaii.meta > metaii.cpp
  
## Process

I hand-compiled Schorre's META II from the paper. Using some C pre-processor macros and some vim tricks I
turned that into a binary. Using the binary I machine compiled META II. I was happy to discover that I only
made two errors in my manual compilation. I missed two "be" instructions. Thankfully the input was well formed
so I did not trigger the defects.

Using the vim tricks again I turned this version into a binary. Then through many iterations I derived my
version of META II that compiles to C++ so that vim tricks are no longer needed. In the process I removed
the following features: .label, .empty, *2, and .num. I added a feature to allow definitions to be forward
declared.
