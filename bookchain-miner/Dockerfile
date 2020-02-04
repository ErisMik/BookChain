# Bookchain - Miner Dockerfile


## Prebuild image
FROM ubuntu:bionic AS build
RUN mkdir -p /bookchain/build
WORKDIR /bookchain/build

RUN apt-get update -y && apt-get install -y build-essential git wget
RUN apt-get update -y && apt-get install -y libssl-dev
RUN bash -c "wget https://github.com/Kitware/CMake/releases/download/v3.16.3/cmake-3.16.3.tar.gz && \
             tar -xzf cmake-3.16.3.tar.gz && \
	     cd cmake-3.16.3 && \
	     ./bootstrap && \
	     make -j$(nproc) && make install"

RUN apt-get update -y && apt-get install -y libboost-dev libboost-test-dev libssl-dev libzmq5-dev libzmqpp-dev
RUN bash -c "git clone https://github.com/oatpp/oatpp.git && \
             cd oatpp && \
             mkdir build && cd build && \
             cmake ../ && \
             make -j$(nproc) && make install"

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

EXPOSE 8000
COPY --from=build /bookchain/build/build/miner ./

CMD ["./miner"]
