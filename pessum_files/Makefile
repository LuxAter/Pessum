CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
COMPILER_FLAGS = -MMD -std=c++11 -w -c
main:$(OBJ_FILES)
%.o: %.cpp %.h
	$(CC) $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp
