FROM emscripten/emsdk:latest

RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    freeglut3-dev \
    libglew-dev \
    libfreetype6-dev \
    ccache \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp
RUN git clone https://github.com/g-truc/glm.git && \
    cd glm && \
    cmake -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -B build . && \
    cmake --build build --parallel && \
    cmake --install build && \
    cd .. && rm -rf glm

WORKDIR /app
COPY . .

RUN make
