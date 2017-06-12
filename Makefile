ifndef .VERBOSE
  .SILENT:
endif

SHELL =               /bin/zsh
export WHITE =        \033[0;37m
export GREEN =        \033[0;32m
export RED =          \033[0;31m
export YELLOW =       \033[0;33m
export NO =           \033[m
export PAD_LENGTH :=  $(shell \
                      maxlength=0; \
                      for file in `find -type f -name '*.cpp' -exec basename {} \;`; do \
                      len=$${\#file}; \
                      if [ $$len -gt $$maxlength ]; then \
                      maxlength=$$len; \
                      fi; \
                      done; \
                      maxlength=$$((maxlength + 13)); \
                      echo $$maxlength )
export PAD :=         $(shell printf '%0.1s' "."{1..$(PAD_LENGTH)})

define checkmark =
  printf "%b\n" "$(GREEN)\xE2\x9C\x94 $(NO)"  
endef

define crossmark =
  printf "%b\n" "$(RED)\xE2\x9D\x8C $(NO)"
endef

export checkmark
export crossmark
export COMPILER = clang++
export FLAGS =    -MMD -std=c++11 -w -c
CPP_FILES =       $(wildcard *.cpp)
TOP_DIR =         $(CPP_FILES:.cpp=.o)
OBJ_FILES :=      $(shell find -name '*.o')
OBJ_LIB :=        $(filter-out ./$(TOP_DIR),$(OBJ_FILES))
LINK =            -std=c++11
NAME =            pessum

all: start $(TOP_DIR) subsystem $(NAME)

$(NAME): $(TOP_DIR) $(OBJ_FILES)
	@str="Compiling $(NAME) source"; \
	  printf '%b%s%*.*s%b' "$(WHITE)" $$str 0 $$(($(PAD_LENGTH) - $${#str})) "$(PAD)" "$(NO)"
	$(COMPILER) $(OBJ_FILES) -o $(NAME) $(LINK) 2> $@.log; \
	  RESULT=$$?; \
	  if [ $$RESULT -ne 0 ]; then \
	    $(crossmark); \
	  else \
	    $(checkmark); \
	  fi; \
	  cat $@.log; \
	  rm -f $@.log

%.o: %.cpp
	@str="Compiling $*.cpp"; \
	  printf '%s%*.*s' $$str 0 $$(($(PAD_LENGTH) - $${#str})) "$(PAD)"
	@$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp 2> $@.log; \
	  RESULT=$$?; \
	  if [ $$RESULT -ne 0 ]; then \
	    $(crossmark); \
	  else \
	    $(checkmark); \
	  fi; \
	  cat $@.log; \
	  rm -f $@.log
	    
.PHONY : start
start:
	@printf "%b" "$(WHITE)Compiling $(NAME)$(NO)\n"

.PHONY : subsystem
subsystem:
	@setterm -fore cyan; printf "$(shell pwd)/$(NAME)_files:\n"; setterm -default
	cd $(NAME)_files && $(MAKE)

.PHONY : clean
clean:
	@printf "%b" "$(WHITE)Cleaning build...$(NO)"
	find . -name "*.o" -type f -delete
	find . -name "*.d" -type f -delete
	$(checkmark)

.PHONY : new
new: clean all

.PHONY : install
install: clean all
	@printf "Installing $(NAME)..."
	cp $(NAME) ~/bin/
	$(checkmark)

.PHONY : log
log:
	log

.PHONY : lib
lib: all
	@if [[ $$UID != 0 ]]; then printf "$(RED)Must run with sudo permision\n$(NO)"; exit 1; fi
	@printf "$(WHITE)Compiling and installing $(NAME)\n$(NO)"
	@printf "Compiling lib$(NAME).a..."
	sudo ar rcs lib$(NAME).a $(OBJ_LIB)
	$(checkmark)
	@printf "Copying lib$(NAME).a to /usr/local/lib/..."
	sudo cp lib$(NAME).a /usr/local/lib/ -u
	$(checkmark)
	@printf "Copying $(NAME).h to /usr/local/include/..."
	sudo cp *.h /usr/local/include/
	$(checkmark)
	@printf "Copying project headers to /usr/local/include/..."
	sudo find . -name '*.hpp' -exec cp --parents \{\} /usr/local/include/ \;
	$(checkmark)

.PHONY : doc-html
doc-html:
	cd docs && $(MAKE) html

.PHONY : doc-latex
doc-latex:
	cd docs && $(MAKE) latexpdf
