PROJECT = s21_containers

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
TESTFLAGS = -lgtest -lgtest_main -pthread
GCOV_FLAG = --coverage

DIR_TESTS = tests/
DIR_BUILD_TESTS = build_tests/

TEST_SRC = $(DIR_TESTS)*.cc
TEST_EXECUTABLE = $(DIR_BUILD_TESTS)$(PROJECT)_test

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open
	GTEST_FLAGS = -lgtest -lgtest_main -pthread
endif
ifeq ($(OS), Darwin)
	OPEN_CMD = open
	LCOV_FLAG = --ignore-errors inconsistent
	GTEST_FLAGS = -lgtest -lgmock -pthread -lgtest_main
endif

all: clean test

test: clean dir
	$(CXX) $(CXXFLAGS) $(GCOV_FLAG) $(TEST_SRC) $(TESTFLAGS) -o $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

dir:
	@mkdir -p $(DIR_BUILD_TESTS)

gcov_report: test
	lcov -t "gcov_report" --ignore-errors mismatch --ignore-errors inconsistent -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

style_check:
	cp ../materials/linters/.clang-format ../src/
	@find . -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Checking {}" && clang-format -n {}'
	@find $(DIR_TESTS) -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Checking {}" && clang-format -n {}'
	rm -rf .clang-format

style_repair: clean
	cp ../materials/linters/.clang-format ../src/
	@find . -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Formatting {}" && clang-format -i {}'
	@find $(DIR_TESTS) -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Formatting {}" && clang-format -i {}'
	rm -rf .clang-format

clean:
	@rm -rf *.a *.o
	@rm -rf $(DIR_BUILD_TESTS)
	@rm -rf *.gcda *.gcno *.info *.dSYM 
	@rm -rf report
