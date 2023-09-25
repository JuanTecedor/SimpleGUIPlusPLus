FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        clang libsdl2-dev libsdl2-image-dev cmake build-essential clang-tidy cppcheck \
    && cd SimpleGUI++ \
    && mkdir build \
    && cmake .. \
    && cmake --build .
