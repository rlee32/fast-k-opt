This will eventually contain LaTeX scripts for a whitepaper.

How is fast-k-opt fast?

Traditional k-opt compares all segments to all other segments.
However, if two segments in a k-opt candidate set are far enough away from each other,
it can be guaranteed that no improving swap is possible.
With this realization, the search radius for each segment can be reduced,
dramatically reducing work while preserving k-optimality.

Work complexity

Employing a search radius would reduce the work complexity from polynomial O(n^k)
to linearithmic O(n * log(n) ^ (k - 1)).
In the linearithmic case, the linear component represents the consideration of every segment
for replacement.
The polylogarithmic component represents the number of segments within the search radius.

Search radius

Computing the search radius follows from comparing the minimum new length to the maximum old length.
If the minimum new length is greater than the maximum old length, then no improvement is possible.

Search radius: minimum new length

In a k-opt exchange, every possible edge swap combination produces new segments that interconnect all old segments.
Therefore, the minimum distance between any 2 segments can be used to estimate the minimum new length.
For a strict lower bound on new length, we can subtract maximum lengths of segments to be considered from
the round-trip, straight-line path between the 2 farthest segments.
This lower bound estimate will be less than or equal to the sum of all new segment lengths.

Search radius: maximum old length

The maximum old length is simply the sum of the k-longest segments of the segments remaining to be considered.


