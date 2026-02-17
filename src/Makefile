CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20
GCOV_FLAG = --coverage

APP_SRC = console_app/*.cc
APP_EXE = s21_simple_navigator
APP_INCLUDE = -I console_app/.

TEST_SRC = libraries/tests/*.cc
TEST_EXE = test
BUILD_PATH = ./
SYSTEM := $(shell uname -s)
GRAPH_INCLUDE = -I libraries/.

GRAPH_SRC = libraries/graph.cc
GRAPH_LIB = libraries/s21_graph.a

GRAPH_ALG_SRC = libraries/graph_algorithms.cc
GRAPH_ALG_LIB = libraries/s21_graph_algorithms.a

TSP_SRC = libraries/tsp.cc 
TSP_OBJ = libraries/tsp.o

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

all: test clean_gcovr

console_app: clean s21_graph s21_graph_algorithms
	$(CC) $(CFLAGS) $(APP_SRC) $(GRAPH_LIB) $(GRAPH_ALG_LIB) -o $(APP_EXE) $(APP_INCLUDE) $(GRAPH_INCLUDE)

test: clean s21_graph_test s21_graph_algorithms_test
	$(CC) $(CFLAGS) $(GCOV_FLAG) $(TEST_SRC) $(LTEST) $(GRAPH_LIB) $(GRAPH_ALG_LIB) -o $(TEST_EXE) $(GRAPH_INCLUDE)
	./$(TEST_EXE) 

s21_graph:
	$(CC) $(CFLAGS) -c $(GRAPH_SRC) $(GRAPH_INCLUDE) -o libraries/graph.o
	ar rcs $(GRAPH_LIB) libraries/graph.o
	rm -rf libraries/graph.o
	ranlib $(GRAPH_LIB)

s21_graph_algorithms:
	$(CC) $(CFLAGS) -c $(GRAPH_ALG_SRC) $(GRAPH_INCLUDE) -o libraries/graph_algorithms.o
	$(CC) $(CFLAGS) -c $(TSP_SRC) $(GRAPH_INCLUDE) -o $(TSP_OBJ)
	ar rcs $(GRAPH_ALG_LIB) libraries/graph_algorithms.o $(TSP_OBJ)
	rm -rf libraries/graph_algorithms.o $(TSP_OBJ)
	ranlib $(GRAPH_ALG_LIB)

s21_graph_test:
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $(GRAPH_SRC) $(GRAPH_INCLUDE) -o libraries/graph.o
	ar rcs $(GRAPH_LIB) libraries/graph.o
	rm -rf libraries/graph.o
	ranlib $(GRAPH_LIB)

s21_graph_algorithms_test:
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $(GRAPH_ALG_SRC) $(GRAPH_INCLUDE) -o libraries/graph_algorithms.o
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $(TSP_SRC) $(GRAPH_INCLUDE) -o $(TSP_OBJ)
	ar rcs $(GRAPH_ALG_LIB) libraries/graph_algorithms.o $(TSP_OBJ)
	rm -rf libraries/graph_algorithms.o $(TSP_OBJ)
	ranlib $(GRAPH_ALG_LIB)

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.log gcov* *.dSYM *.a libraries/*.o \
	libraries/*.a libraries/tests/output/* libraries/*.gc* $(APP_EXE) $(TEST_EXE) \
	*.dot 

clean_gcovr:
	rm -rf *.gc* libraries/*.gc*

gcov_report: clean test
	mkdir -p report
	gcovr --exclude 'libraries/tests/.*'  --exclude 's21_containers/.*' --exclude '.*\.h' \
	--exclude-unreachable-branches --exclude-throw-branches --html-details report/index.html \
	--html-medium-threshold 80 --html-high-threshold 95 --html-title "CPP_Simple_Navigator coverage report"
	rm -rf *.gc* libraries/*.gc*

style:
	clang-format --style=google -i ./libraries/*.h ./libraries/*.cc ./libraries/tests/*.cc \
	./console_app/*.cc ./console_app/*.h

style_check:
	clang-format --style=google -n ./libraries/*.h ./libraries/*.cc ./libraries/tests/*.cc \
	./console_app/*.cc ./console_app/*.h
