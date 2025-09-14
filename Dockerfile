FROM ubuntu:22.04

# Install dependencies for Qt5 build + ninja
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    qtbase5-dev \
    qt5-qmake \
    qtbase5-dev-tools \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace