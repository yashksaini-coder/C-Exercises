.DEFAULT_GOAL := help
CC ?= cc
V ?= 0
Q := $(if $(filter 1,$(V)),,@)
CPPFLAGS += -Iinclude -I. -Itests -D_POSIX_C_SOURCE=200809L -D_DEFAULT_SOURCE -D_DARWIN_C_SOURCE
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -g -O0
LDLIBS ?= -lpthread -lm
FIRST := 1
LAST := 116
NUMBERS := $(shell seq $(FIRST) $(LAST))
IDS := $(shell printf '%03d\n' $(NUMBERS))
BUILD := build/default
SOURCE_DIR := exercises
ifeq ($(SOLUTION),1)
BUILD := build/solution
SOURCE_DIR := solutions
endif
ifeq ($(SANITIZE),1)
BUILD := $(BUILD)-sanitized
override CFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
override LDFLAGS += -fsanitize=address,undefined
endif

ifneq ($(filter run test,$(MAKECMDGOALS)),)
ifneq ($(filter $(N),$(NUMBERS)),$(N))
$(error Choose an exercise: make run N=1 or make test N=1 (N must be $(FIRST) through $(LAST)))
endif
ifneq ($(words $(N)),1)
$(error N must be a single number from $(FIRST) through $(LAST))
endif
ID := $(shell printf '%03d' $(N))
endif

TEST_SOURCES := tests/support.c tests/main.c $(wildcard tests/stage*.c)
HEADERS := include/exercises.h lib.h tests/support.h
.PHONY: help run test check build test-all FORCE
help:
	@printf '%s\n' \
	  'make run N=1          Run your playground main for exercise 1' \
	  'make test N=1         Test your implementation of exercise 1' \
	  'make test-all         Test every exercise (summary only)' \
	  'make check            Syntax/type-check all exercises and tests' \
	  'make build            Build all playgrounds and test executables' \
	  'Add V=1 to show compilation commands.' \
	  'Add SANITIZE=1 to enable AddressSanitizer and UBSan.' \
	  'Add SOLUTION=1 to run the reference solution instead of your code.'

run: $(BUILD)/$(ID)-run
	@./$<

test: $(BUILD)/$(ID)-test $(BUILD)/test-runner
	@$(BUILD)/test-runner $<

test-all: $(BUILD)/test-runner
	@pass=0; fail=0; for n in $(NUMBERS); do \
	  id=$$(printf '%03d' $$n); \
	  if $(MAKE) --no-print-directory test N=$$n SOLUTION=$(SOLUTION) SANITIZE=$(SANITIZE) >/dev/null 2>&1; then \
	    pass=$$((pass+1)); printf 'PASS %s\n' $$id; \
	  else fail=$$((fail+1)); printf 'FAIL %s\n' $$id; fi; \
	done; printf '\n%d passed, %d failed\n' $$pass $$fail; [ $$fail -eq 0 ]

$(BUILD)/test-runner: tools/run_tests.c FORCE
	@mkdir -p $(BUILD)
	$(Q)$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD)/%-run: $(SOURCE_DIR)/%.c lib.c $(HEADERS) FORCE
	@mkdir -p $(BUILD)
	$(Q)$(CC) $(CPPFLAGS) $(CFLAGS) $< lib.c $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD)/%-test: $(SOURCE_DIR)/%.c lib.c $(HEADERS) $(TEST_SOURCES) FORCE
	@mkdir -p $(BUILD)
	$(Q)$(CC) $(CPPFLAGS) $(CFLAGS) -DEXERCISE_TEST -DEXERCISE=$(shell expr $* + 0) $< lib.c $(TEST_SOURCES) $(LDFLAGS) $(LDLIBS) -o $@

check:
	$(Q)$(CC) $(CPPFLAGS) $(CFLAGS) -fsyntax-only tools/run_tests.c
	$(Q)set -e; for id in $(IDS); do \
	  n=$$(expr $$id + 0); \
	  $(CC) $(CPPFLAGS) $(CFLAGS) -fsyntax-only $(SOURCE_DIR)/$$id.c lib.c; \
	  $(CC) $(CPPFLAGS) $(CFLAGS) -DEXERCISE_TEST -DEXERCISE=$$n -fsyntax-only $(SOURCE_DIR)/$$id.c lib.c $(TEST_SOURCES); \
	done
	@printf '%s\n' 'All exercises and test suites passed syntax/type checking.'

build: $(BUILD)/test-runner $(foreach id,$(IDS),$(BUILD)/$(id)-run $(BUILD)/$(id)-test)
