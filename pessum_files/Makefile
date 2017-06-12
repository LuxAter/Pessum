SHELL =     /bin/zsh
CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES) subsystem

%.o: %.cpp %.hpp
	@str="Compiling $*.cpp"; \
	  printf '%s%*.*s' "$$str" 0 $$(($(PAD_LENGTH) - $${#str})) "$(PAD)"	  
	@$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp 2> $@.log; \
	  RESULT=$$?; \
	  if [ $$RESULT -ne 0 ]; then \
	    $(crossmark); \
	  else \
	    $(checkmark); \
	  fi; \
	  cat $@.log; \
	  rm -f $@.log

.PHONY : subsystem
subsystem:
