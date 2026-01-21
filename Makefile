AR=ar
CC=gcc
CXX=g++

INC_DIR = ./include
SRC_DIR = ./src
BIN_DIR = ./bin
OBJ_DIR = ./obj
LIB_DIR = ./lib
TESTSRC_DIR = ./testsrc
TESTOBJ_DIR = ./testobj
TESTBIN_DIR = ./testbin
TESTCOVER_DIR = ./htmlconv

DEFINES =
INCLUDES += -I $(INC_DIR)
CFLAGS += 
CPPFLAGS += -std=c++17
LDFLAGS = 

TEST_CFLAGS = $(CFLAGS) -O0 -g --coverage
TEST_CPPFLAGS = $(CPPFLAGS) -fno-inline
TEST_LDFLAGS = $(LDFLAGS) -lgtest -lgtest_main -lpthread



TEST_OBJ_FILES = $(TESTOBJ_DIR)/StringUtilsTest.o $(TESTOBJ_DIR)/StringUtils.o

TEST_TARGET = $(TESTBIN_DIR)/teststrutils



all: directories runtests

runtests: $(TEST_TARGET)
	$(TEST_TARGET)
	lcov --capture --directory . --output-file $(TESTCOVER_DIR)/coverage.info --ignore-errors inconsistent,source
	lcov --remove $(TESTCOVER_DIR)/coverage.info '/usr/*' '*/testsrc/*' --output-file $(TESTCOVER_DIR)/coverage.info
	genhtml $(TESTCOVER_DIR)/coverage.info --output-directory $(TESTCOVER_DIR)

$(TEST_TARGET): $(TEST_OBJ_FILES)
	$(CXX) $(TEST_CFLAGS) $(TEST_CPPFLAGS) $(TEST_OBJ_FILES) $(TEST_LDFLAGS) -o $(TEST_TARGET)

$(TESTOBJ_DIR)/StringUtils.o: $(SRC_DIR)/StringUtils.cpp
	$(CXX) $(TEST_CFLAGS) $(TEST_CPPFLAGS) $(DEFINES) $(INCLUDES) -c $(SRC_DIR)/StringUtils.cpp -o $(TESTOBJ_DIR)/StringUtils.o

$(TESTOBJ_DIR)/StringUtilsTest.o: $(TESTSRC_DIR)/StringUtilsTest.cpp
	$(CXX) $(TEST_CFLAGS) $(TEST_CPPFLAGS) $(DEFINES) $(INCLUDES) -c $(TESTSRC_DIR)/StringUtilsTest.cpp -o $(TESTOBJ_DIR)/StringUtilsTest.o


.PHONY: directories
directories: 
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(TESTBIN_DIR)
	mkdir -p $(TESTOBJ_DIR)
	mkdir -p $(TESTCOVER_DIR)

clean::
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_DIR)
	rm -rf $(TESTBIN_DIR)
	rm -rf $(TESTOBJ_DIR)
	rm -rf $(TESTCOVER_DIR)

.PHONY: clean
