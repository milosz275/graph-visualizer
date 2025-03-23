CC = ccache emcc

SRC_WEB = $(shell find src/ -name '*.cpp')
OBJ_WEB = $(patsubst src/%.cpp, build/%.o, $(SRC_WEB))
OUT_WEB = build/graph-visualizer.js

COMMON_CFLAGS = -std=c++20 \
	-Wall \
	-Wextra \
	-pedantic \
	-O3 \
	-gsource-map

CC_FLAGS = -Wno-nullability-completeness \
	-Wno-nullability-extension \
	-Wno-gnu-zero-variadic-macro-arguments \
	-Iinclude/web \
	-Iinclude/model \
	-Iinclude/view \
	-Iinclude/controller \
	-I/usr/local/include \
	-I/usr/include/freetype2 \
	-I/usr/include/libpng16

LDFLAGS = -s USE_WEBGL2=1 \
	-s FULL_ES3=1 \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s NO_EXIT_RUNTIME=1 \
	-s WASM=1 \
	-s USE_FREETYPE=1 \
	--shell-file src/index.html # -sASSERTIONS=2 -sSAFE_HEAP=1

all: web

web: $(OUT_WEB)

$(OUT_WEB): $(OBJ_WEB)
	$(CC) $(COMMON_CFLAGS) $(CC_FLAGS) $(OBJ_WEB) -o $(OUT_WEB) $(LDFLAGS)

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(COMMON_CFLAGS) $(CC_FLAGS) -c $< -o $@

clean:
	find build -type f ! -name 'index.html' ! -name 'favicon.ico' -delete
	find build -type d -empty -delete

.PHONY: all clean
