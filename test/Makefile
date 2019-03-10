GTEST_DIR = ./googletest-master


USER_DIR = ../src
TEST_DIR = .


CPPFLAGS += -isystem $(GTEST_DIR)/include


CXXFLAGS += -std=c++0x -g -Wall -Wextra -pthread -Wno-missing-field-initializers


TESTS = all_test


GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h



all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o  QMatrix.o test_QMatrix.o test_Qlearner.o test_png.o test_config_reader.o config_reader.o png.o lodepng.o Qlearner.o 


run: all_test
	./all_test
# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o :	$(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o :	$(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

lodepng.o : $(USER_DIR)/png/lodepng.cpp $(USER_DIR)/png/lodepng.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/png/lodepng.cpp

png.o : $(USER_DIR)/png/png.cpp $(USER_DIR)/png/png.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/png/png.cpp

config_reader.o : $(USER_DIR)/config_reader.cpp $(USER_DIR)/config_reader.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/config_reader.cpp

Qlearner.o : $(USER_DIR)/Qlearner.cpp $(USER_DIR)/Qlearner.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Qlearner.cpp


QMatrix.o : $(USER_DIR)/QMatrix.cpp $(USER_DIR)/QMatrix.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/QMatrix.cpp 

test_QMatrix.o : $(TEST_DIR)/test_QMatrix.cpp \
                     $(USER_DIR)/QMatrix.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/test_QMatrix.cpp

test_Qlearner.o : $(TEST_DIR)/test_Qlearner.cpp \
                     $(USER_DIR)/Qlearner.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/test_Qlearner.cpp


test_png.o : $(TEST_DIR)/test_png.cpp \
                     $(USER_DIR)/png/png.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/test_png.cpp


test_config_reader.o : $(TEST_DIR)/test_config_reader.cpp \
                     $(USER_DIR)/config_reader.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/test_config_reader.cpp


all_test :config_reader.o png.o lodepng.o Qlearner.o QMatrix.o test_config_reader.o test_png.o test_Qlearner.o test_QMatrix.o  gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
