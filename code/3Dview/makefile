# object files
OBJ = main.o draw.o
# header files
DEPS = draw.h
# libraries
LIBS = -lX11 -lGL -lGLU
# compiler flags
CXXFLAGS = -std=c++11

# compile to .o
%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CXXFLAGS) $(LIBS)

#Combine them into the output file
3Dview: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS) $(LIBS)

#Cleanup
.PHONY: clean

clean:
	rm -f $(OBJ) *~ core *~

