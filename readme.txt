This quadtree-based k-opt algorithm runs in O(n * log(n) ^ (k - 1)), instead of O(n ^ k) (the state of the art for best-improvement).
This is not an approximation algorithm! This algorithm achieves local optimality, providing the same solution quality as O(n^k) algorithms, just a lot more efficiently!

The python scripts verify TSPLIB-formatted files and provide visualizations for k-opt edge exchanges.

Compilation:
1. Make sure "CXX" in "k-opt/makefile" is set to the desired compiler.
2. Run "make" in "k-opt/".

Running:
1. Run "./k-opt.out" for usage details.

Style notes:
1. Namespaces follow directory structure. If an entire namespace is in a single header file, the header file name will be the namespace name.
2. Headers are grouped from most to least specific to this repo (e.g. repo header files will come before standard library headers).

Potential design changes:
1. Moving Quadtree insertion and erasure implementation to QuadtreeNodes, and DepthMap as a static member of QuadtreeNode.
4. Placing all segments in an unordered set, and holding indexes to these segments in QuadtreeNodes (instead of the segments themselves).

TODO:
1. Write tour to file.
2. Utilize candidate set bounding box to abort distance computations.
3. Rename DepthMap to DepthTable.
4. Compare distances on the first two points in a candidate set to elminate further candidate checking.
5. Store segment margins, instead of recomputing every iteration.
6. Search radius relaxation parameter, and first-improvement (vs. best-improvement) search.
    Would allow for faster arrival to "good" grids, on which the unrelaxed algorithm can run.
    This would be especially useful because search radius is proportional to maximum segment lengths at each depth.
