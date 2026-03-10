.PHONY: all rebuild install uninstall test gcov_report clean style style_check

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20
GCOV = --coverage

SYSTEM := $(shell uname -s)

BIN_DIR = bin
BUILD_DIR = build
TEST_OUTPUT_DIR = tests/output

APP_NAME = s21_simple_navigator
TEST_EXE = $(BIN_DIR)/test

GRAPH_LIB = $(BUILD_DIR)/s21_graph.a
GRAPH_ALG_LIB = $(BUILD_DIR)/s21_graph_algorithms.a

GRAPH_SRC = src/libraries/graph.cc
GRAPH_ALG_SRC = src/libraries/graph_algorithms.cc
TSP_SRC = src/libraries/tsp.cc

APP_SRC := $(wildcard src/console_app/*.cc)
TEST_SRC := $(wildcard tests/*.cc)

INCLUDES = -I src -I src/libraries -I src/console_app

GRAPH_OBJ = $(BUILD_DIR)/graph.o
GRAPH_ALG_OBJ = $(BUILD_DIR)/graph_algorithms.o
TSP_OBJ = $(BUILD_DIR)/tsp.o

ifeq ($(SYSTEM), Linux)
	LTEST = -lgtest -lsubunit -lm -lrt -pthread
	OPEN_CMD = xdg-open
else ifeq ($(SYSTEM), Darwin)
	LTEST = -lgtest -lgtest_main
	OPEN_CMD = open
else
	$(error Unsupported system: $(SYSTEM))
endif

all: install

rebuild: clean all

install: $(GRAPH_LIB) $(GRAPH_ALG_LIB)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(APP_SRC) $(GRAPH_LIB) $(GRAPH_ALG_LIB) -o $(BIN_DIR)/$(APP_NAME) $(INCLUDES)

uninstall:
	rm -rf $(BIN_DIR)

# ================= LIBRARIES =================

$(GRAPH_LIB): $(GRAPH_OBJ)
	mkdir -p $(BUILD_DIR)
	ar rcs $@ $^

$(GRAPH_ALG_LIB): $(GRAPH_ALG_OBJ) $(TSP_OBJ)
	mkdir -p $(BUILD_DIR)
	ar rcs $@ $^

$(BUILD_DIR)/graph.o: $(GRAPH_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(BUILD_DIR)/graph_algorithms.o: $(GRAPH_ALG_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(BUILD_DIR)/tsp.o: $(TSP_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# ================= TESTS =================

test: clean $(GRAPH_LIB) $(GRAPH_ALG_LIB)
	mkdir -p $(BIN_DIR) $(TEST_OUTPUT_DIR)
	$(CC) $(CFLAGS) $(TEST_SRC) $(GRAPH_LIB) $(GRAPH_ALG_LIB) $(LTEST) -o $(TEST_EXE) $(INCLUDES)
	./$(TEST_EXE)

# ================= COVERAGE =================

gcov_report: clean
gcov_report: CFLAGS += $(GCOV)
gcov_report: test
	mkdir -p report
	gcovr \
	--filter 'src/libraries/.*\.cc' \
	--exclude-unreachable-branches \
	--exclude-throw-branches \
	--html-details report/index.html \
	--html-medium-threshold 80 \
	--html-high-threshold 95 \
	--html-title "CPP_Simple_Navigator coverage report"
	$(OPEN_CMD) report/index.html

# ================= UTILITIES =================

style:
	find . -name "*.cc" -o -name "*.h" | xargs clang-format --style=google -i

style_check:
	find . -name "*.cc" -o -name "*.h" | xargs clang-format --style=google -n

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	rm -rf report
	rm -rf $(TEST_EXE)
	rm -rf $(TEST_OUTPUT_DIR)
	rm -rf *.gc*