#//311318075
#//shanibasteker@gmail.com

# Variables
CXX = g++
# With Coverage falgs
CXXFLAGS = -std=c++11 -Wall -I/usr/include/SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target
TARGET = main

# Object files
OBJS = Complex.o main.o

TEST_OBJ = tests.o

# Rules
all: $(TARGET) tests

tree: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

tests: Complex.o tests.o
	$(CXX) Complex.o tests.o -o tests $(LDFLAGS)

Complex.o: Complex.cpp Complex.hpp
	$(CXX) -c Complex.cpp -o Complex.o $(CXXFLAGS)

Demo.o: Demo.cpp Tree.hpp Complex.hpp
	$(CXX) -c Demo.cpp -o Demo.o $(CXXFLAGS)

tests.o: tests.cpp Tree.hpp Complex.hpp
	$(CXX) -c tests.cpp -o tests.o $(CXXFLAGS)

# Phony targets
.PHONY: clean all tests coverage html_report

clean:
	rm -f $(OBJS) $(TARGET) tests.o tests *.gcno *.gcda *.gcov coverage.info
	rm -rf out

coverage: all
	./$(TARGET)
	@gcov $(SRCS)

html_report: coverage
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

