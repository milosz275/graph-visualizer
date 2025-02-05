# Compiler
CXX = g++
EMCC = emcc

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra
EMCCFLAGS = -std=c++20 -Wall -Wextra

# Include directories
INCLUDES = -Iinclude

# Libraries
CLIBS = 
CXXLIBS = 
EMCCLIBS = 

# Source files
CXXSRCS = $(wildcard src/*.cpp)

# Object files
CXXOBJS = $(CXXSRCS:src/%.cpp=build/src/%.o)
EMCCOBJS = $(CXXSRCS:src/%.cpp=build/src/%.emcc.o)

# Executable name
MAIN = main
EMCC_MAIN = main.html

.PHONY: default all debug clean depend emcc

default: all

all: $(MAIN)
	@echo "Project has been compiled"

debug: CXXFLAGS += -g -DDEBUG -D_DEBUG
debug: $(MAIN)
	@echo "Project has been compiled in debug mode"

emcc: $(EMCC_MAIN)
	@echo "Project has been compiled for web"

$(MAIN): $(CXXOBJS)
	@mkdir -p build/bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o build/bin/$(MAIN) $(CXXOBJS) $(CXXLIBS)

$(EMCC_MAIN): $(EMCCOBJS)
	@mkdir -p build/bin
	$(EMCC) $(EMCCFLAGS) $(INCLUDES) -o build/bin/$(EMCC_MAIN) $(EMCCOBJS) $(EMCCLIBS)

build/src/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

build/src/%.emcc.o: src/%.cpp
	@mkdir -p $(@D)
	$(EMCC) $(EMCCFLAGS) $(INCLUDES) -c $<  -o $@

depend: $(CXXSRCS)
	makedepend $(INCLUDES) $^

clean:
	$(RM) build/src/*.o
	$(RM) build/bin/$(MAIN)
	$(RM) build/bin/$(EMCC_MAIN)
	$(RM) build/bin/$(MAIN).js
	$(RM) build/bin/$(MAIN).wasm
	$(RM) build/lib/*.a

# Include dependency files
-include $(CXXSRCS:.cpp=.d)
	