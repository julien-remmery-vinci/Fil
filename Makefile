# MIT License
# 
# Copyright (c) 2025 Julien Remmery
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
PROJECT_NAME := fil

SRC := fil.c
INCLUDE := fil.h

MAIN_SRC := main.c
TEST_SRC := test.c

MAIN_TARGET := main
TEST_TARGET := test
LIB_TARGET := libfil

CC := gcc
CFLAGS :=

all: main_build test_build lib_build

.PHONY: main_build
main_build: $(SRC) $(INCLUDE) $(MAIN_SRC)
	$(CC) $(CFLAGS) -o $(MAIN_TARGET) $(SRC) $(MAIN_SRC)

.PHONY: test_build
test_build: $(SRC) $(INCLUDE) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(SRC) $(TEST_SRC)

.PHONY: lib_build
lib_build: $(SRC) $(INCLUDE)
	$(CC) $(CFLAGS) -fPIC -c $(SRC) -o $(PROJECT_NAME).o
	$(CC) -shared -o $(LIB_TARGET).so $(PROJECT_NAME).o

.PHONY: test
test: test_build
	@./$(TEST_TARGET)

.PHONY: clean
clean:
	rm -rf $(MAIN_TARGET) $(TEST_TARGET) *.o $(LIB_TARGET).so