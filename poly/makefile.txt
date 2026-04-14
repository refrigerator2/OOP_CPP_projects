CXX = g++

CXXFLAGS = -g -Wall -pedantic -std=c++17

CXXFLAGS_ADD = $(CXXFLAGS) -fno-elide-constructors

TARGET = test	

TARGET_ADD = testflag

SRCS = TestPoly.cpp Poly.cpp

OBJS = $(SRCS:.cpp=.o)

OBJS_ADD = $(SRCS:.cpp=_fl.o)

all: $(TARGET) $(TARGET_ADD)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
$(TARGET_ADD): $(OBJS_ADD)
	$(CXX) $(CXXFLAGS_ADD) -o $(TARGET_ADD) $(OBJS_ADD)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
%_fl.o: %.cpp
	$(CXX) $(CXXFLAGS_ADD) -c $< -o $@

run: $(TARGET)
	valgrind ./$(TARGET)
run_flag: $(TARGET_ADD)
	valgrind ./$(TARGET_ADD)

clean:
	rm -f $(OBJS) $(OBJS_ADD) $(TARGET) $(TARGET_ADD)    
