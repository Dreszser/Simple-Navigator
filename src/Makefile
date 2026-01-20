CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20
GCOVFLAGS = -fprofile-arcs -ftest-coverage
#LTEST = -lgtest -lgtest_main
TEST_SRC = libraries/tests/*.cc
EXE = test
BUILD_PATH = ./
SYSTEM := $(shell uname -s)
GRAPH_INCLUDE = -I libraries/.
GRAPH_SRC = libraries/graph.cc
GRAPH_LIB = libraries/s21_graph.a

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

test: clean s21_graph
	$(CC) $(CFLAGS) $(TEST_SRC) $(LTEST) $(GRAPH_LIB) -o $(EXE) -pthread $(GRAPH_INCLUDE)
	./$(EXE) 

s21_graph:
	$(CC) $(CFLAGS) $(GRAPH_SRC) -c -o libraries/graph.o -pthread $(GRAPH_INCLUDE)
	ar rcs $(GRAPH_LIB) libraries/graph.o
	rm -rf libraries/graph.o
	ranlib $(GRAPH_LIB)

clean:
	rm -rf *.o *.g* *.info *.out report *.a test *.log gcov* *.dSYM *.a libraries/*.o \
	libraries/*.a

gcov_flag:
	$(eval CFLAGS += --coverage $(GCOVFLAGS))

gcov_report: clean gcov_flag test
ifeq ($(SYSTEM), Linux)
	lcov --no-external -c -d . -o line_coverage.info
	lcov --remove line_coverage.info "*/s21_containers/tree/*" -o coverage.info
	genhtml coverage.info -o report
	open report/index.html
else
	lcov --no-external --ignore-errors inconsistent -c -d . -o line_coverage.info
	lcov --remove line_coverage.info "*/s21_containers/tree/*" --ignore-errors inconsistent -o coverage.info
	genhtml --ignore-errors inconsistent --ignore-errors corrupt coverage.info -o report
	open report/index.html
endif

style:
	@find s21_containers \( -name "*.tpp*" -or -name "*.h" \) -exec clang-format --style=google -i {} +
	@find tests \( -name "*.cc*" -or -name "*.h" \) -exec clang-format --style=google -i {} +
	@echo "All C++ source files and headers formatted with Google style."

style_check:
	@find s21_containers \( -name "*.tpp*" -or -name "*.h" \) -exec clang-format --style=google -n {} +
	@find tests \( -name "*.cc*" -or -name "*.h" \) -exec clang-format --style=google -n {} +

rebuild:
	make all