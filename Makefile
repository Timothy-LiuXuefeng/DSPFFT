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
	mkdir -p ./build/include/prior
	mkdir -p ./build/bin
	ar -o ./build/bin/libdspfft.a -cr ./src/prior/bin/*.o ./src/dspfft/bin/*.o
	cp -r ./src/prior/include ./build/include/prior/
	cp ./src/dspfft/include/* ./build/include/

.PHONY: test
test:
	make -C ./src/homework "COMPILER_OPTIONS=$(COMPILER_OPTIONS)"
	mkdir -p ./build/test
	cp ./src/homework/bin/main.out ./build/test/
	chmod +x ./build/test/main.out

.PHONY: $(PROJECTS)
$(PROJECTS):
	make -C ./src/$@ "COMPILER_OPTIONS=$(COMPILER_OPTIONS)"

CLEAN_PROJECTS=$(patsubst %,clean_%,$(PROJECTS))

.PHONY: clean, CLEAN_PROJECTS
clean: $(CLEAN_PROJECTS)

$(CLEAN_PROJECTS):
	-rm -rf ./build/*
	-rmdir ./build
	make -C ./src/homework clean
	make -C $(patsubst clean_%,./src/%,$@) clean
