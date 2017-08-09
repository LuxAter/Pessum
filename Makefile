SHELL = /bin/bash

export NAME=pessum
export LINK=
export INCLUDE=
export TYPE=lib

export SOURCE_DIR=source
export TEST_DIR=test
export EXTERNAL_DIR=external
export BUILD_DIR=build
export INCLUDE_DIR=include

export BASE_PATH=$(shell pwd)

export COMPILER=g++
export CXXFLAGS= -MMD -std=c++11 -w -c

export INSTALL_PATH=/user/local/

export GCOV_LINK = -lgcov --coverage
export GCOV_FLAG = -fprofile-arcs -ftest-coverage

export COMMON_INCLUDE=-I$(BASE_PATH)/$(INCLUDE_DIR) $(INCLUDE)

export SECTION_COLOR=\033[1;97m
export TARGET_COLOR=\033[0;34m
export LINK_COLOR=\033[0;35m
export CLEAN_COLOR=\033[0;33m
export COMPILE_COLOR=\033[0;32m
export NO_COLOR=\033[m

ifndef .VERBOSE
  .SILENT:
endif

define print_section
str="$(1)";\
    line_length=$${#str};\
    printf "%b%s\n" "$(SECTION_COLOR)" "$$str";\
    while [ $$line_length -gt 0 ]; do\
      printf "=";\
      let line_length=line_length-1;\
    done;\
    printf "%b\n" "$(NO_COLOR)"
endef

define help
printf "%b%*s%b: %s\n" "$(TARGET_COLOR)" 14 "$(1)" "$(NO_COLOR)" "$(2)"
endef

.PHONY : all
all: external source test 

.PHONY : clean
clean: clean-external clean-source clean-test

.PHONY : help
help:
	$(call print_section,Makefile Help)
	printf "List of all acceptable make targets\n\n"
	$(call help,all,Builds external, source, and test files and projects)
	$(call help,clean,Clean files created from external, source, and test)
	$(call help,help,Display this help page)
	$(call help,external,Builds external files and projects)
	$(call help,clean-external,Cleans files created from external)
	$(call help,source,Builds source files and projects)
	$(call help,clean-source,Cleans files created from source)
	$(call help,test,Builds test files and projects)
	$(call help,clean-test,Cleans files created from test)

.PHONY : external 
external:	
	$(call print_section,External Dependencies)
	if [ -d "$(EXTERNAL_DIR)" ]; then cd "$(EXTERNAL_DIR)" && $(MAKE); fi
.PHONY : clean-external 
clean-external:	
	$(call print_section,External Dependencies)
	if [ -d "$(EXTERNAL_DIR)" ]; then cd "$(EXTERNAL_DIR)" && $(MAKE) clean; fi

.PHONY : source
source:
	$(call print_section,Source Files)
	if [ -d "$(SOURCE_DIR)" ]; then cd "$(SOURCE_DIR)" && $(MAKE); fi
.PHONY : clean-source
clean-source:
	$(call print_section,Source Files)
	if [ -d "$(SOURCE_DIR)" ]; then cd "$(SOURCE_DIR)" && $(MAKE) clean; fi

.PHONY : test
test:
	$(call print_section,Unit Tests)
	if [ -d "$(TEST_DIR)" ]; then cd "$(TEST_DIR)" && $(MAKE); fi
.PHONY : clean-test
clean-test:
	$(call print_section,Unit Tests)
	if [ -d "$(TEST_DIR)" ]; then cd "$(TEST_DIR)" && $(MAKE) clean; fi
