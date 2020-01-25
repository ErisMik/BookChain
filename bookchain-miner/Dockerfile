# Bookchain - Miner Dockerfile


## Prebuild image
FROM ubuntu:bionic AS build
RUN mkdir -p /bookchain/build
WORKDIR /bookchain/build

RUN apt-get update -y && apt-get install -y git build-essential cmake clang-tidy
RUN apt-get update -y && apt-get install -y libboost-dev libboost-test-dev libssl-dev libzmq5-dev libzmqpp-dev

RUN mkdir -p /bookchain/build/build
COPY thirdparty/ ./thirdparty
COPY CMakeLists.txt ./
COPY src/ ./src

WORKDIR /bookchain/build/build
RUN cmake ../ && make -j8


## Runtime image
FROM ubuntu:bionic AS run
RUN mkdir -p /bookchain/miner
WORKDIR /bookchain/miner

RUN apt-get update -y && apt-get install -y gdb
RUN apt-get update -y && apt-get install -y libboost-dev libssl-dev libzmq5

COPY --from=build /bookchain/build/build/miner ./

CMD ["./miner"]
