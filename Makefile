CXX = g++
CXXFLAGS = -Wall -g
TARGET = program
all: $(basic_calculator)
	./$(TARGET)
$(TARGET): basic_calculator.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) basic_calculator.cpp
clean:
	rm -f $(TARGET)