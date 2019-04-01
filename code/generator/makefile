# object files
OBJ = main.o cube.o animation/animation.o animation/animBall.o animation/animRain.o animation/animGrow.o output/output.o output/outputGraphics.o output/outputNetwork.o
# header files
DEPS = main.h cube.h animation/animation.h animation/animBall.h animation/animRain.h animation/animGrow.h output/output.h output/outputGraphics.h output/outputNetwork.h
# libraries
LIBS =
# compiler flags
CXXFLAGS = -std=c++11

objects = $(wildcard *.o)

# compile to .o
.cpp.o:
	g++ $(CXXFLAGS) -o $@ -g -c $<

#Combine them into the output file
generator: $(OBJ)
	g++ $(CXXFLAGS) -o $@ -g $^ $(LIBS)

#Cleanup
.PHONY: clean

clean:
	rm -f generator $(OBJ) *~ core *~

