In progress; transferring code from 2opt repo.

The goal is to implement a k-opt algorithm that runs in O(n * log(n) ^ (k - 1)), instead of O(n ^ k).

To reduce the complexity of the c++ implementation, I offload as much as possible to python scripts.
The c++ implementation is meant to read and output point sets and tours.
The python verification_scripts are meant to post-process the c++ output.

Compilation:
1. Make sure "CXX" in "k-opt/makefile" is set to the desired compiler.
2. Run "make" in "k-opt/".

Running:
1. Run "./k-opt.out" for usage details.

Style notes:
1. Namespaces follow directory structure. If an entire namespace is in a single header file, the header file name will be the namespace name.
2. Headers are grouped from most to least specific to this repo (e.g. repo header files will come before standard library headers).

Design propositions:
1. Moving Quadtree insertion and erasure implementation to QuadtreeNodes, and DepthMap as a static member of QuadtreeNode.
