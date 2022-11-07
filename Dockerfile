FROM ubuntu AS base

# Core tools
RUN apt-get update && apt-get install -y \
    clang \
    make \
    cmake \
    git

FROM base AS tester

# Catch2
WORKDIR /catch2

RUN git clone https://github.com/catchorg/Catch2.git 
RUN cd Catch2 && cmake -Bbuild -H. -DBUILD_TESTING=OFF && cmake --build build/ --target install

WORKDIR /test

COPY include/ include/
COPY test/ test/
COPY CMakeLists.txt .
COPY makefile .

CMD ["make"]

