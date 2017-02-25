export COMPILER = clang++
export COMPILER_FLAGS = -MMD -std=c++11 -w -c
CPP_FILES = $(wildcard *.cpp)
TOP_DIR = $(notdir $(CPP_FILES:.cpp=.o))
OBJ_FILES = $(wildcard */*.o)
OBJ_FILES += $(wildcard */*/*.o)
OBJ_FILES += $(wildcard */*/*/*.o)
OBJ_FILES += $(wildcard */*/*/*/*.o)
OBJ_FILES += $(wildcard */*/*/*/*/*.o)
OBJ_FILES += $(wildcard */*/*/*/*/*/*.o)
LINKER_FLAGS = 
PROGRAM_NAME = pessum

all: $(TOP_DIR) subsystem $(PROGRAM_NAME)
	@setterm -fore green
	@printf "==========>Successfuly compiled $(PROGRAM_NAME)<==========\n"
	@setterm -fore white

$(PROGRAM_NAME): $(TOP_DIR) $(OBJ_FILES)
	@setterm -fore red
	@printf "==========>CORE<==========\n"
	@setterm -fore white
	$(COMPILER) $(TOP_DIR) $(OBJ_FILES) -o $(PROGRAM_NAME) $(LINKER_FLAGS)

%.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@cd pessum_files && $(MAKE)

.PHONY : clean
clean:
	rm -f *.o
	rm -f *.d
	rm -f */*.o
	rm -f */*.d
	rm -f */*/*.o
	rm -f */*/*.d
	rm -f */*/*/*.o
	rm -f */*/*/*.d
	rm -f */*/*/*/*.o
	rm -f */*/*/*/*.d
	rm -f */*/*/*/*/*.o
	rm -f */*/*/*/*/*.d
	clear
	@echo Cleared all '.o' and '.d' files

.PHONY : tar
tar: clean
	tar -zcvf $(PROGRAM_NAME).tar.gz ../Aequus

.PHONY : lib
lib: all
	ar rcs lib$(PROGRAM_NAME).a $(TOTAL_OBJ_FILES)
	sudo cp lib$(PROGRAM_NAME).a /usr/local/lib/ -u
	sudo cp *.h /usr/local/include/
	sudo find . -name '*.hpp' -exec cp --parents \{\} /usr/local/include/ \;
	@echo Compiled lib file, and copied to usr/local/lib

.PHONY : log
log:
	@less output.log

.PHONY : help
help:
	@printf "make\nmake clean\nmake tar\nmake lib\nmake log\nmake new\nmake todo\n"


.PHONY : new
new: clean all

.PHONY : todo
todo:
	@less TODO
