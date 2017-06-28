SHELL = /bin/bash

export SOURCE_DIR = source
export TEST_DIR = 
export BUILD_DIR = build

export COMPILER = clang++
export CPPFLAGS = -MMD -std=c++11 -w -c
export LINK = 
export NAME = pessum

export RED = \033[0;31m
export GREEN = \033[0;32m
export YELLOW = \033[0;33m
export BLUE = \033[0;34m
export MAGENTA = \033[0;35m
export CYAN = \033[0;36m
export WHITE = \033[0;37m
export NO_COLOR = \033[m

export BUILD_COLOR = $(BLUE)
export DIR_COLOR = $(MAGENTA)
export ERR_COLOR = $(RED)
export OK_COLOR = $(GREEN)
export CLEAN_COLOR = $(YELLOW)

export WIDTH=$(shell printf $$(($(call FindLongestFile, $(SOURCE_DIR)) + 13)))
export BASE_PATH=$(shell pwd)

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

all: start source-make test-make 
	printf "%b%s%b\n" "$(WHITE)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	printf "%b\n" "$(WHITE)Compleated Compiling $(NAME)$(NO_COLOR)"

.PHONY : clean
clean: start-clean source-clean test-clean
	printf "%b%s%b\n" "$(CLEAN_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	printf "%b\n" "$(CLEAN_COLOR)Compleated Cleaning$(NO_COLOR)"

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

.PHONY : start
start:
	printf "%b\n" "$(WHITE)Compiling $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(WHITE)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"

.PHONY : start-clean
start-clean:
	printf "%b\n" "$(CLEAN_COLOR)Cleaning $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(CLEAN_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"

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
	if [[ "$(TEST_DIR)" -ne "" ]]; then printf "%b\n" "$(BUILD_COLORS)TEST$(NO_COLOR)"; cd $(TEST_DIR) && $(MAKE); fi

.PHONY : test-clean
test-clean:
	if [[ "$(TEST_DIR)" -ne "" ]]; then printf "%b\n" "$(CLEAN_COLOR)TEST$(NO_COLOR)"; cd $(TEST_DIR) && $(MAKE) clean; fi


