# Makefile for CityMatcher

CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic

TARGET = main
OBJS = main.o User.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp User.h
	$(CXX) $(CXXFLAGS) -c main.cpp

User.o: User.cpp User.h
	$(CXX) $(CXXFLAGS) -c User.cpp

clean:
	rm -f *.o $(TARGET)