SHELL = /bin/bash

export SOURCE_DIR = source
export TEST_DIR = test 
export BUILD_DIR = build
export GTEST_DIR = external/googletest/googletest
export GH_PAGES_SOURCE = docs/source docs/Makefile

export COMPILER = g++
export CPPFLAGS = -MMD -std=c++11 -w -c
export LINK = 
export NAME = pessum
export TYPE = lib

export LIB_PATH = /usr/local/
export EXE_PATH = ~/bin/

export GCOV_LINK = -fprofile-arcs
export GCOV_FLAG = -fprofile-arcs -ftest-coverage

export RED = \033[0;31m
export GREEN = \033[0;32m
export YELLOW = \033[0;33m
export BLUE = \033[0;34m
export MAGENTA = \033[0;35m
export CYAN = \033[0;36m
export WHITE = \033[0;37m
export NO_COLOR = \033[m

export BUILD_COLOR = $(BLUE)
export ERR_COLOR = $(RED)
export OK_COLOR = $(GREEN)
export CLEAN_COLOR = $(YELLOW)
export INSTALL_COLOR = $(MAGENTA)

export WIDTH=$(shell printf $$(($(call FindLongestFile, $(SOURCE_DIR)) + 19)))
export BASE_PATH=$(shell pwd)
export LINE=$(call Line,$(WIDTH),.)

ifndef .VERBOSE
  .SILENT:
endif

define FindLongestFile
$(shell \
  max=0; \
  for file in `find $(1) -type f -exec basename {} \;`; do \
    len=$${#file}; \
    if [ $$len -gt $$max ]; then \
      max=$$len; \
    fi; \
  done; \
  echo $$max
)
endef

define Line = 
$(shell printf '%0.1s' "$(2)"{1..$(1)})
endef

define Print
var="$(1)"; \
    width="$(2)";\
    printf '%s%*.*s' "$$var" 0 $$(($$width - $${#var} - 1)) "$(call Line,$(2),.)"
endef


define PrintCpp
var="$(1)"; \
    var=$${var%.*}.cpp; \
    width="$(2)";\
    printf '%s%*.*s' "$$var" 0 $$(($$width - $${#var} - 1)) "$(call Line,$(2),.)"
endef

define Compile
mkdir -p $(@D)
if [[ $(2) == Linking ]]; then \
  var="$(2) $(@F)";\
  width="$(WIDTH)";\
  printf '%s%*.*s' "$$var" 0 $$(($$width - $${#var} - 1)) "$(LINE)"; \
else \
  var="$(2) $(@F)";\
  var=$${var%.*}.cpp;\
  width="$(WIDTH)";\
  printf '%s%*.*s' "$$var" 0 $$(($$width - $${#var} - 1)) "$(LINE)"; \
fi
$(1) 2> $@.log; \
  RESULT=$$?; \
  if [ $$RESULT -ne 0 ]; then \
    printf "%b\n" "$(ERR_COLOR)\xE2\x9D\x8C $(NO_COLOR)"; \
  else \
    printf "%b\n" "$(OK_COLOR)\xE2\x9C\x94 $(NO_COLOR)"; \
  fi; \
  cat $@.log; \
  rm -f $@.log
endef

define check =
  printf "%b\n" "$(OK_COLOR)\xE2\x9C\x94 $(NO_COLOR)"
endef

define cross =
  printf "%b\n" "$(ERR_COLOR)\xE2\x9D\x8C $(NO_COLOR)"
endef

all: start googletest-make source-make test-make 
	printf "%b%s%b\n" "$(WHITE)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	printf "%b\n" "$(WHITE)Compleated Compiling $(NAME)$(NO_COLOR)"

.PHONY : clean
clean: start-clean googletest-clean source-clean test-clean
	#if [[ -e compile_commands.json ]]; then rm compile_commands.json; fi
	if [[ -e $(BUILD_DIR)/lib$(NAME).a ]]; then rm $(BUILD_DIR)/lib$(NAME).a; fi
	printf "%b%s%b\n" "$(CLEAN_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	printf "%b\n" "$(CLEAN_COLOR)Compleated Cleaning$(NO_COLOR)"

.PHONY : purge
purge: uninstall clean

.PHONY : new
new: clean all

.PHONY : docs
docs: docs-html docs-latex

.PHONY : docs-html
docs-html:
	cd docs && $(MAKE) html

.PHONY : docs-latex
docs-latex:
	cd docs && $(MAKE) latexpdf

.PHONY : gh-pages
gh-pages:
	git checkout gh-pages
	rm * -r
	git checkout master $(GH_PAGES_SOURCE)
	git reset HEAD
	mv $(GH_PAGES_SOURCE) .
	make latex
	make html
	mv -fv build/html/* ./
	git add -A
	git commit -m"Generated gh-pages for `git log master -1 --pretty=short --abbrev-commit`" && git push origin gh-pages; git checkout master

.PHONY : install
ifeq ($(TYPE),lib)
install: all
	$(eval SOURCE_HEADERS = $(shell cd $(SOURCE_DIR) && find . -name '*.hpp' -or -name '*.h'))
	$(eval LIB_OBJ = $(filter-out $(BASE_PATH)/$(BUILD_DIR)/$(SOURCE_DIR)/main.o, $(shell find $(BASE_PATH)/$(BUILD_DIR)/$(SOURCE_DIR)/*.o)))
	@if [[ $$UID != 0 ]]; then \
	  printf "%b\n" "$(ERR_COLOR)Must run with root permissions$(NO_COLOR)"; \
	else \
	  printf "%b\n" "$(INSTALL_COLOR)Installing $(NAME) lib$(NO_COLOR)"; \
	  printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	  $(call Print,Compiling library,$(WIDTH)); \
	  sudo ar rcs $(BUILD_DIR)/lib$(NAME).a $(LIB_OBJ); \
	  if [[ -e $(BUILD_DIR)/lib$(NAME).a ]]; then \
	    $(call check); \
	    $(call Print,Copying library,$(WIDTH)); \
	    sudo cp $(BUILD_DIR)/lib$(NAME).a $(LIB_PATH)/lib/ -u; \
	    $(call check); \
	    $(call Print,Copying headers,$(WIDTH)); \
	    if [[ ! -d $(LIB_PATH)/include/$(NAME) ]]; then sudo mkdir $(LIB_PATH)/include/$(NAME); fi;\
	    cd $(SOURCE_DIR) && sudo cp $(SOURCE_HEADERS) $(LIB_PATH)/include/$(NAME)/ -r -u ; \
	    $(call check); \
	  else \
	    $(call cross); \
	  fi;\
	  printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	  printf "%b\n" "$(INSTALL_COLOR)Installed $(NAME) lib$(NO_COLOR)"; \
	fi 

else
install:all
	printf "%b\n" "$(INSTALL_COLOR)Installing $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	$(call Print,Copying $(NAME),$(WIDTH))
	cp $(NAME) $(EXE_PATH) -u
	$(call check)
	printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	printf "%b\n" "$(INSTALL_COLOR)Installed $(NAME)$$(NO_COLOR)"; \

endif

.PHONY : uninstall
ifeq ($(TYPE),lib)
uninstall:
	@if [[ $$UID != 0 ]]; then \
	  printf "%b\n" "$(ERR_COLOR)Must run with root permissions$(NO_COLOR)"; \
	else \
	  printf "%b\n" "$(INSTALL_COLOR)Uninstalling $(NAME) lib$(NO_COLOR)"; \
	  printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	  if [[ -e $(LIB_PATH)/lib/lib$(NAME).a ]]; then \
	    $(call Print,Deleting library,$(WIDTH)); \
	    sudo rm $(LIB_PATH)/lib/lib$(NAME).a; \
	    $(call check); \
	  fi; \
	  if [[ -d $(LIB_PATH)/include/$(NAME) ]]; then \
	    $(call Print,Deleting header files,$(WIDTH)); \
	    sudo rm $(LIB_PATH)/include/$(NAME)/ -r; \
	    $(call check); \
	  fi; \
	  printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	  printf "%b\n" "$(INSTALL_COLOR)Uninstalled $(NAME) lib$(NO_COLOR)"; \
	fi 


else
uninstall:
	printf "%b\n" "$(INSTALL_COLOR)Uninstalling $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	$(call Print,Deleting ~/bin/$(NAME),$(WIDTH))
	rm $(NAME) $(EXE_PATH) -u
	$(call check)
	printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	printf "%b\n" "$(INSTALL_COLOR)Uninstalled $(NAME)$$(NO_COLOR)"; \

endif

.PHONY : start
start:
	printf "%b\n" "$(WHITE)Compiling $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(WHITE)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"

.PHONY : start-clean
start-clean:
	printf "%b\n" "$(CLEAN_COLOR)Cleaning $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(CLEAN_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"

.PHONY : start-gtest
start-gtest:
	printf "%b\n" "$(BUILD_COLOR)GOOGLE TEST$(NO_COLOR)"

.PHONY : googletest-make
googletest-make: start-gtest $(BASE_PATH)/$(BUILD_DIR)/gtest/gtest-all.o $(BASE_PATH)/$(BUILD_DIR)/gtest/gtest_main.o
	@ar -rc $(BUILD_DIR)/libgtest.a $(BUILD_DIR)/gtest/gtest-all.o
	@ar -rc $(BUILD_DIR)/libgtest_main.a $(BUILD_DIR)/gtest/gtest_main.o

.PHONY : googletest-clean
googletest-clean:
	printf "%b\n" "$(CLEAN_COLOR)GOOGLE TEST$(NO_COLOR)"
	$(call Print,Cleaning gtest/*.o,$(WIDTH))
	if [ -d "$(BUILD_DIR)/gtest" ]; then find $(BASE_PATH)/$(BUILD_DIR)/gtest -name "*.o" -type f -delete; fi
	$(call check)
	$(call Print,Cleaning lib*.a,$(WIDTH))
	if [ -e "$(BUILD_DIR)/libgtest.a" ]; then rm $(BUILD_DIR)/libgtest.a; fi
	if [ -e "$(BUILD_DIR)/libgtest_main.a" ]; then rm $(BUILD_DIR)/libgtest_main.a; fi
	$(call check)

.PHONY : source-make
source-make:
	printf "%b\n" "$(BUILD_COLOR)SOURCE$(NO_COLOR)"
	cd $(SOURCE_DIR) && $(MAKE)

.PHONY : source-clean
source-clean:
	printf "%b\n" "$(CLEAN_COLOR)SOURCE$(NO_COLOR)"
	cd $(SOURCE_DIR) && $(MAKE) clean

.PHONY : test-make
test-make:
	printf "%b\n" "$(BUILD_COLOR)TEST$(NO_COLOR)"
	cd $(TEST_DIR) && $(MAKE)

.PHONY : test-clean
test-clean:
	printf "%b\n" "$(CLEAN_COLOR)TEST$(NO_COLOR)"
	cd $(TEST_DIR) && $(MAKE) clean

$(BASE_PATH)/$(BUILD_DIR)/gtest/gtest-all.o:
	$(call Compile,$(COMPILER) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc -o $(BUILD_DIR)/gtest/gtest-all.o,Compiling)

$(BASE_PATH)/$(BUILD_DIR)/gtest/gtest_main.o:
	$(call Compile,$(COMPILER) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest_main.cc -o $(BUILD_DIR)/gtest/gtest_main.o,Compiling)
