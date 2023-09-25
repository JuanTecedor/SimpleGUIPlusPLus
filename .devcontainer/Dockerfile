FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        clang libsdl2 cmake build-essential \
    && cd SimpleGUI++ \
    && mkdir build \
    && cmake -S/home/juan/Dev/SimpleGUI++ -B/home/juan/Dev/SimpleGUI++/build \
    && cmake --build /home/juan/Dev/SimpleGUI++/build --config Debug --target all --
