# Bookchain - Miner Dockerfile


## Prebuild image
FROM ubuntu:bionic AS build
RUN mkdir -p /bookchain/build
WORKDIR /bookchain/build

RUN apt-get update -y && apt-get install -y git build-essential cmake
RUN apt-get update -y && apt-get install -y libboost-dev libboost-test-dev libssl-dev libzmq5-dev libzmqpp-dev
RUN bash -c "git clone https://github.com/oatpp/oatpp.git && \
             cd oatpp && \
             mkdir build && cd build && \
             cmake ../ && \
             make -j8 && make install"

ARG CMAKE_ARGS=""

RUN mkdir -p /bookchain/build/build
COPY thirdparty/ ./thirdparty
COPY CMakeLists.txt ./
COPY test/ ./test
COPY src/ ./src

WORKDIR /bookchain/build/build
RUN cmake ${CMAKE_ARGS} ../ && make -j8


## Runtime image
FROM ubuntu:bionic AS run
RUN mkdir -p /bookchain/miner
WORKDIR /bookchain/miner

RUN apt-get update -y && apt-get install -y gdb
RUN apt-get update -y && apt-get install -y libboost-dev libssl-dev libzmq5

ENV LD_LIBRARY_PATH /bookchain/miner
COPY --from=build /bookchain/build/build/miner /bookchain/build/build/libbookchain.so ./

CMD ["./miner"]
