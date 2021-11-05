COMPILER_OPTIONS?=g++ -std=c++11 -O2 -Wall -Wpedantic -Wextra -Werror
COMPILER_ALL_OPTIONS=$(COMPILER_OPTIONS)

BIN_DIR=./bin
DEPS_DIR=./deps
RAW_OBJECTS=$(patsubst ./cpp/%.cpp,%.o,$(shell ls ./cpp/*.cpp))
# DEBUG_TARGET=$(BIN_DIR)/libprior.a
OBJECTS=$(patsubst %.o,$(BIN_DIR)/%.o,$(RAW_OBJECTS))
DEPS=$(patsubst %.o, $(DEPS_DIR)/%.d,$(RAW_OBJECTS))

.PHONY: build, debug

build: $(OBJECTS)

# debug: $(DEBUG_TARGET)

# $(DEBUG_TARGET): $(OBJECTS)
# 	ar -o $@ -cr $^

$(DEPS): $(DEPS_DIR)/%.d: ./cpp/%.cpp | $(DEPS_DIR)
	$(COMPILER_ALL_OPTIONS) -o $@ -MM $<

$(OBJECTS): $(BIN_DIR)/%.o: ./cpp/%.cpp | $(BIN_DIR)
	$(COMPILER_ALL_OPTIONS) -o $@ -c $<

$(DEPS_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

include $(DEPS)

.PHONY: clean
clean:
	-rm $(OBJECTS) $(DEPS)
# 	-rm $(DEBUG_TARGET) $(OBJECTS) $(DEPS)
	-rmdir $(DEPS_DIR) $(BIN_DIR)
