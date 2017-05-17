# ifndef .VERBOSE
#   .SILENT:
# endif
export COMPILER = clang++
export FLAGS = -MMD -std=c++11 -w -c
CPP_FILES = $(wildcard *.cpp)
TOP_DIR = $(CPP_FILES:.cpp=.o)
OBJ_FILES := $(shell find -name '*.o')
OBJ_LIB := $(filter-out ./$(TOP_DIR),$(OBJ_FILES))
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
	@setterm -fore cyan; printf "$(shell pwd)/pessum_files:\n"; setterm -fore white
	@cd pessum_files && $(MAKE)

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

.PHONY : lib
lib: all
	printf "Compiling lib$(NAME).a...\n"
	ar rcs lib$(NAME).a $(OBJ_LIB)
	printf "Copying lib$(NAME).a to /usr/local/lib/...\n"
	sudo cp lib$(NAME).a /usr/local/lib/ -u
	printf "Copying $(NAME).h to /usr/local/include/...\n"
	sudo cp *.h /usr/local/include/
	printf "Copying project headers to /usr/local/include/...\n"
	sudo find . -name '*.hpp' -exec cp --parents \{\} /usr/local/include/ \;
	setterm -fore green
	printf "==========>>>>>>>>>>Compiled Installed Lib<<<<<<<<<<==========\n"
	setterm -fore white
