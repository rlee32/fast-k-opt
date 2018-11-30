CXX = g++-8
CXX_FLAGS = -std=c++17 -fopenmp # important flags.
CXX_FLAGS += -Wall -Wextra -Werror -pedantic # source code quality.
CXX_FLAGS += -O3 -ffast-math # optimization.
CXX_FLAGS += -g # debugging.

SRCS = k-opt.cpp PointSet.cpp Tour.cpp \
    quadtree/MortonKey.cpp

%.o: %.cpp; $(CXX) $(CXX_FLAGS) -o $@ -c $<

OBJS = $(SRCS:.cpp=.o)

all: $(OBJS); $(CXX) $^ -o k-opt.out

clean: ; rm -rf k-opt.out $(OBJS) *.dSYM
