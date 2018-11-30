In progress; transferring code from 2opt repo.

The goal is to implement a k-opt algorithm that runs in O(n * log(n) ^ (k - 1)), instead of O(n ^ k).

To reduce the complexity of the c++ implementation, I offload as much as possible to python scripts.
The c++ implementation is meant to read and output point sets and tours.
The python verification_scripts are meant to post-process the c++ output.


