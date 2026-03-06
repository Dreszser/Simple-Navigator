CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20
GCOV_FLAG = --coverage

APP_SRC = src/console_app/*.cc
APP_INCLUDE = -I src/console_app/.
BIN_DIR = bin
APP_EXE = s21_simple_navigator

TEST_SRC = tests/*.cc
TEST_EXE = test
TEST_OUTPUT_DIR = tests/output

# BUILD_PATH = ./
SYSTEM := $(shell uname -s)
GRAPH_INCLUDE = -I src/libraries/. -I src/.

GRAPH_SRC = src/libraries/graph.cc
GRAPH_LIB = src/libraries/s21_graph.a

GRAPH_ALG_SRC = src/libraries/graph_algorithms.cc
GRAPH_ALG_LIB = src/libraries/s21_graph_algorithms.a

TSP_SRC = src/libraries/tsp.cc 
TSP_OBJ = src/libraries/tsp.o


ifeq ($(SYSTEM), Linux)
	OPEN_CMD = xdg-open
	LTEST = -lgtest -lsubunit -lm -lrt -pthread
else ifeq ($(SYSTEM), Darwin)
	OPEN_CMD = open
	LTEST = -lgtest -lgtest_main
else
	$(error Unsupported system: $(SYSTEM))
endif

rebuild: clean all

all: gcov_report install

install: clean s21_graph s21_graph_algorithms
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(APP_SRC) $(GRAPH_LIB) $(GRAPH_ALG_LIB) -o $(BIN_DIR)/$(APP_EXE) $(APP_INCLUDE) $(GRAPH_INCLUDE)

uninstall:
	rm -rf $(BIN_DIR)

test: clean s21_graph_test s21_graph_algorithms_test
	mkdir -p ${TEST_OUTPUT_DIR}
	$(CC) $(CFLAGS) $(GCOV_FLAG) $(TEST_SRC) $(LTEST) $(GRAPH_LIB) $(GRAPH_ALG_LIB) -o $(TEST_EXE) $(GRAPH_INCLUDE)
	./$(TEST_EXE) 

s21_graph:
	$(CC) $(CFLAGS) -c $(GRAPH_SRC) $(GRAPH_INCLUDE) -o src/libraries/graph.o
	ar rcs $(GRAPH_LIB) src/libraries/graph.o
	rm -rf src/libraries/graph.o
	ranlib $(GRAPH_LIB)

s21_graph_algorithms:
	$(CC) $(CFLAGS) -c $(GRAPH_ALG_SRC) $(GRAPH_INCLUDE) -o src/libraries/graph_algorithms.o
	$(CC) $(CFLAGS) -c $(TSP_SRC) $(GRAPH_INCLUDE) -o src/libraries/tsp.o
	ar rcs $(GRAPH_ALG_LIB) src/libraries/graph_algorithms.o src/libraries/tsp.o
	rm -rf src/libraries/graph_algorithms.o src/libraries/tsp.o
	ranlib $(GRAPH_ALG_LIB)

s21_graph_test:
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $(GRAPH_SRC) $(GRAPH_INCLUDE) -o src/libraries/graph.o
	ar rcs $(GRAPH_LIB) src/libraries/graph.o
	rm -rf src/libraries/graph.o
	ranlib $(GRAPH_LIB)

s21_graph_algorithms_test:
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $(GRAPH_ALG_SRC) $(GRAPH_INCLUDE) -o src/libraries/graph_algorithms.o
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $(TSP_SRC) $(GRAPH_INCLUDE) -o src/libraries/tsp.o
	ar rcs $(GRAPH_ALG_LIB) src/libraries/graph_algorithms.o src/libraries/tsp.o
	rm -rf src/libraries/graph_algorithms.o src/libraries/tsp.o
	ranlib $(GRAPH_ALG_LIB)

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.log gcov* *.dSYM *.a 
	rm -rf src/libraries/{*.o,*.a,*.gc*}
	rm -rf $(TEST_OUTPUT_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(TEST_EXE) *.dot

clean_gcovr:
	rm -rf *.gc* src/libraries/*.gc*

gcov_report: clean test
	mkdir -p report
	gcovr --exclude 'tests/.*'  --exclude 'src/s21_containers/.*' --exclude 'src/.*\.h' \
	--exclude-unreachable-branches --exclude-throw-branches --html-details report/index.html \
	--html-medium-threshold 80 --html-high-threshold 95 --html-title "CPP_Simple_Navigator coverage report"
	rm -rf *.gc* src/libraries/*.gc*

style:
	find . -name "*.cpp" -o -name "*.h" | xargs clang-format --style=google -i

style_check:
	find . -name "*.cpp" -o -name "*.h" | xargs clang-format --style=google -n
