OBJS = Source.cpp
CPPPESSUMOBJS = Pessum/logging.cpp Pessum/lux_reader.cpp Pessum/pessum_core.cpp Pessum/rest.cpp
HPESSUMOBJS = Pessum/logging.h Pessum/lux_reader.h Pessum/pessum_core.h Pessum/rest.h
CC = g++
COMPILER_FLAGS = -std=c++11
LINKER_FLAGS = -lSDL2
OBJ_NAME = Pessum_Test
all : $(OBJS)
		$(CC) $(HPESSUMOBJS) $(CPPPESSUMOBJS) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
