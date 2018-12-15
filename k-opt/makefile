CXX = g++-8
CXX_FLAGS = -std=c++17 -fopenmp # important flags.
CXX_FLAGS += -Wall -Wextra -Werror -pedantic -Wfatal-errors # source code quality.
CXX_FLAGS += -O3 -ffast-math # optimization.
CXX_FLAGS += -g # debugging.
CXX_FLAGS += -I./ # include paths.

SRCS = k-opt.cpp PointSequence.cpp Optimizer.cpp \
    fileio/PointSet.cpp fileio/Tour.cpp \
    quadtree/Quadtree.cpp quadtree/QuadtreeNode.cpp \
    quadtree/depth_map/DepthMap.cpp \
    quadtree/LengthTable.cpp \
    optimizer/SegmentIterator.cpp optimizer/NodeIterator.cpp

%.o: %.cpp; $(CXX) $(CXX_FLAGS) -o $@ -c $<

OBJS = $(SRCS:.cpp=.o)

all: $(OBJS); $(CXX) $^ -o k-opt.out

clean: ; rm -rf k-opt.out $(OBJS) *.dSYM
