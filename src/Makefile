CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20 --coverage

TEST_SRC = libraries/tests/*.cc
EXE = test
BUILD_PATH = ./
SYSTEM := $(shell uname -s)
GRAPH_INCLUDE = -I libraries/. -I .

GRAPH_SRC = libraries/graph.cc
GRAPH_LIB = libraries/s21_graph.a

GRAPH_ALG_SRC = libraries/graph_algorithms.cc
GRAPH_ALG_LIB = libraries/s21_graph_algorithms.a

ifeq ($(SYSTEM), Linux)
	OPEN_CMD = xdg-open
	LTEST = -lgtest -lsubunit -lm -lrt -pthread
else ifeq ($(SYSTEM), Darwin)
	OPEN_CMD = open
	LTEST = -lgtest -lgtest_main
else
	$(error Unsupported system: $(SYSTEM))
endif

all: clean test

test: clean s21_graph s21_graph_algorithms
	$(CC) $(CFLAGS) $(TEST_SRC) $(LTEST) $(GRAPH_LIB) $(GRAPH_ALG_LIB) -o $(EXE) $(GRAPH_INCLUDE)
	./$(EXE) 

s21_graph:
	$(CC) $(CFLAGS) -c $(GRAPH_SRC) $(GRAPH_INCLUDE) -o libraries/graph.o
	ar rcs $(GRAPH_LIB) libraries/graph.o
	rm -rf libraries/graph.o
	ranlib $(GRAPH_LIB)

s21_graph_algorithms:
	$(CC) $(CFLAGS) -c $(GRAPH_ALG_SRC) $(GRAPH_INCLUDE) -o libraries/graph_algorithms.o
	ar rcs $(GRAPH_ALG_LIB) libraries/graph_algorithms.o
	rm -rf libraries/graph_algorithms.o
	ranlib $(GRAPH_ALG_LIB)

clean:
	rm -rf *.o *.g* *.info *.out report *.a test *.log gcov* *.dSYM *.a libraries/*.o \
	libraries/*.a libraries/tests/output/* libraries/*.gc*

gcov_report: clean test
	mkdir -p report
	gcovr --exclude 'libraries/tests/.*'  --exclude 's21_containers/.*' \
	--exclude-unreachable-branches --exclude-throw-branches --html-details report/index.html \
	--html-medium-threshold 80 --html-high-threshold 95 --html-title "CPP_Simple_Navigator coverage report"
	rm -rf *.gc* libraries/*.gc*

style:
	@find s21_containers \( -name "*.tpp*" -or -name "*.h" \) -exec clang-format --style=google -i {} +
	@find tests \( -name "*.cc*" -or -name "*.h" \) -exec clang-format --style=google -i {} +
	@echo "All C++ source files and headers formatted with Google style."

style_check:
	@find s21_containers \( -name "*.tpp*" -or -name "*.h" \) -exec clang-format --style=google -n {} +
	@find tests \( -name "*.cc*" -or -name "*.h" \) -exec clang-format --style=google -n {} +

rebuild:
	make all