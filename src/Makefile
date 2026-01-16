CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
GCOVFLAGS = -fprofile-arcs -ftest-coverage
#LTEST = -lgtest -lgtest_main
TEST_SRC = tests/*.cc
EXE = test
BUILD_PATH = ./
SYSTEM := $(shell uname -s)

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

test: clean 
	$(CC) $(CFLAGS) $(TEST_SRC) $(LTEST) -o $(EXE) -pthread 
	./$(EXE) 

clean:
	rm -rf *.o *.g* *.info *.out report *.a test *.log gcov* *.dSYM

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