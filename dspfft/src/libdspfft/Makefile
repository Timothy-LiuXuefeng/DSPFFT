
COMPILER_OPTIONS?=g++ -std=c++11 -O2 -Wall -Wpedantic -Wextra -Werror

ADDITIONAL_INCLUDE=-I../..
COMPILER_ALL_OPTIONS=$(COMPILER_OPTIONS)

BIN_DIR=./bin
DEPS_DIR=./deps
RAW_OBJECTS=$(patsubst %.cpp,%.o,$(shell ls *.cpp))
TARGET=$(BIN_DIR)/libdspfft.a
OBJECTS=$(patsubst %.o,$(BIN_DIR)/%.o,$(RAW_OBJECTS))
DEPS=$(patsubst %.o, $(DEPS_DIR)/%.d,$(RAW_OBJECTS))

$(shell mkdir -p $(DEPS_DIR))
$(shell mkdir -p $(BIN_DIR))

$(TARGET): $(OBJECTS)
	ar -o $@ -cr $^

$(DEPS): $(DEPS_DIR)/%.d: %.cpp
	$(COMPILER_ALL_OPTIONS) $(ADDITIONAL_INCLUDE) -o $@ -MM $<

$(OBJECTS): $(BIN_DIR)/%.o: %.cpp
	$(COMPILER_ALL_OPTIONS) $(ADDITIONAL_INCLUDE) -o $@ -c $<

include $(DEPS)

.PHONY: clean
clean:
	-rm $(TARGET) $(OBJECTS) $(DEPS)
	-rmdir $(DEPS_DIR) $(BIN_DIR)
