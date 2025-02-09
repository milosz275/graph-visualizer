EMCC = emcc

SRC = triangle.cpp
OUT = triangle.js

CFLAGS = -std=c++17 -pedantic \
	-s USE_WEBGL2=1 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 \
	-Wno-nullability-completeness -Wno-nullability-extension \
	-I$EMSDK/upstream/emscripten/cache/sysroot/include \
	-I$FREEGLUT/include/GL

LDFLAGS = -s USE_WEBGL2=1 -s FULL_ES3=1 --shell-file index.html

all: $(OUT)

$(OUT): $(SRC)
	$(EMCC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT) $(OUT).wasm $(OUT).data
