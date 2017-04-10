ifndef VERBOSE
.SILENT:
endif
export COMPILER = clang++
export FLAGS = -MMD -std=c++11 -w -c
CPP_FILES = $(wildcard *.cpp)
TOP_DIR = $(notdir $(CPP_FILES:.cpp=.o))
OBJ_FILES := $(shell find -name '*.o')
LINK =
NAME = pessum

all: $(TOP_DIR) subsystem $(NAME)
	@setterm -fore green
	@printf "==========>>>>>>>>>>Compiled $(NAME)<<<<<<<<<<==========\n"
	@setterm -fore white

$(NAME): $(TOP_DIR) $(OBJ_FILES)
	@setterm -fore red
	@printf ">>>>>>>>>>----------Core Compile----------<<<<<<<<<<\n"
	@setterm -fore white
	$(COMPILER) $(OBJ_FILES) -o $(NAME) $(LINK)

%.o: %.cpp
	@printf "Compiling $*.cpp...\n"
	@$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@cd pessum_src && $(MAKE)

.PHONY : clean
clean:
	@setterm -fore red
	@printf "Removing *.o files\n"
	@find . -name "*.o" -type f -delete
	@printf "Removing *.d files\n"
	@find . -name "*.d" -type f -delete
	@printf "Removed all *.o and *.d files\n"
	@setterm -fore white

.PHONY : new
new: clean all

.PHONY : install
install: clean all
	cp $(NAME) ~/bin/

.PHONY : log
log:
	less output.log
