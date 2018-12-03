In progress; transferring code from 2opt repo.

The goal is to implement a k-opt algorithm that runs in O(n * log(n) ^ (k - 1)), instead of O(n ^ k).

To reduce the complexity of the c++ implementation, I offload as much as possible to python scripts.
The c++ implementation is meant to read and output point sets and tours.
The python verification_scripts are meant to post-process the c++ output.

Preparation:
1. Make sure the Makefile's c++ compiler is correct for your system.

Style notes (I would love to hear critiques):
1. Namespaces always follow directory names, unless the entire namespace is in a single header file.
    Then, the namespace will follow the directory names and the header file name.
2. Headers are listed and grouped from most specific to this repo to standard libraries.

Design propositions:
1. Moving Quadtree insertion and erasure implementation to QuadtreeNodes, and DepthMap as a static member of QuadtreeNode.
