EMCC = emcc

SRC = src/main.cpp
OUT = build/graph.js

CFLAGS = -std=c++17 -Wall -Werror -pedantic \
	-s USE_WEBGL2=1 \
	-s FULL_ES3=1 \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s NO_EXIT_RUNTIME=1 \
	-s WASM=1 \
	-Wno-nullability-completeness -Wno-nullability-extension \
	-Wno-gnu-zero-variadic-macro-arguments \
	-Iinclude \
	-I$EMSDK/upstream/emscripten/cache/sysroot/include \
	-I$FREEGLUT/include/GL \
	-DEMSCRIPTEN_GUI=1

LDFLAGS = -s USE_WEBGL2=1 \
	-s FULL_ES3=1 \
	--shell-file src/index.html

all: $(OUT)

$(OUT): $(SRC)
	mkdir -p $(dir $(OUT))
	$(EMCC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -rf build/*
