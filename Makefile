TARGET = cp_math.so

SRC = cp_math.cpp

all:
	g++ -O3 -Wall -shared -std=c++11 -fPIC $$(python3 -m pybind11 --includes) $(SRC) -o $(TARGET)

clean:
	rm -f *.so
