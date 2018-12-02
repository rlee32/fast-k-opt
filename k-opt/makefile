CXX = g++-8
CXX_FLAGS = -std=c++17 -fopenmp # important flags.
CXX_FLAGS += -Wall -Wextra -Werror -pedantic -Wfatal-errors # source code quality.
CXX_FLAGS += -O2 -ffast-math # optimization.
CXX_FLAGS += -g # debugging.
CXX_FLAGS += -I./ # include paths.

SRCS = k-opt.cpp \
    fileio/PointSet.cpp fileio/Tour.cpp \
    quadtree/morton_keys.cpp quadtree/QuadtreeNode.cpp quadtree/Quadtree.cpp \
    point_sequence/PointSequence.cpp

%.o: %.cpp; $(CXX) $(CXX_FLAGS) -o $@ -c $<

OBJS = $(SRCS:.cpp=.o)

all: $(OBJS); $(CXX) $^ -o k-opt.out

clean: ; rm -rf k-opt.out $(OBJS) *.dSYM
