COMPILER?=g++
CPP_STANDARD?=-std=c++11
OPTIMIZATION?=-O2
WARNING_LEVEL?=-Wall -Wpedantic -Wextra -Werror
PREDEFINED_MACRO?=
COMPILER_OPTIONS=$(COMPILER) $(CPP_STANDARD) $(OPTIMIZATION) $(WARNING_LEVEL) $(PREDEFINED_MACRO)

PROJECTS=prior dspfft

.PHONY: build
build: $(PROJECTS)
	mkdir -p ./build
	mkdir -p ./build/include
	ar -o ./build/libdspfft.a -cr ./src/prior/bin/*.o ./src/dspfft/bin/*.o
	cp -r ./src/prior/include ./build/include/prior/
	cp ./src/dspfft/include/* ./build/include/

.PHONY: test
test: build
	make -C ./src/homework "COMPILER_OPTIONS=$(COMPILER_OPTIONS)"
	cp ./src/homework/bin/main.out ./build/

.PHONY: $(PROJECTS)
$(PROJECTS):
	make -C ./src/$@ "COMPILER_OPTIONS=$(COMPILER_OPTIONS)"

CLEAN_PROJECTS=$(patsubst %,clean_%,$(PROJECTS))

.PHONY: clean, CLEAN_PROJECTS
clean: $(CLEAN_PROJECTS)

$(CLEAN_PROJECTS):
	-rm ./build/libdspfft.a
	-rmdir ./build
	make -C $(patsubst clean_%,./src/%,$@) clean
